//
//  P5Native.h
//  TruID
//
//  Pipeline P5's image work, for Swift: the Android SDK's native P5 steps (P5Steps, a line-for-line port of
//  the C2CL package's p5_reference.py) behind two classes. The two networks themselves run in Swift
//  (P5Processor); their raw inputs and outputs cross here as float32 data.
//

#import <CoreGraphics/CoreGraphics.h>
#import <CoreVideo/CoreVideo.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// The gate's pictures of one crop, for the self-test and for working through a session afterwards: the
/// names of the C2CL package's test vectors.
typedef NS_ENUM(NSInteger, P5DebugImage) {
    /// `1_mask`: the segmentation, binary.
    P5DebugImageMask = 0,
    /// `1_soft`: the segmentation, feathered inwards.
    P5DebugImageSoft,
    /// `G_canvas`: the gate model's grey canvas.
    P5DebugImageGateCanvas,
    /// `G_canvas_mask`: the mask beside it.
    P5DebugImageGateCanvasMask,
};

/// One finger's upright 500 ppi crop, and what pipeline P5 makes of it (Android's P5Engine around P5Steps):
///
/// - the gate (step G): `segmentationInputWithSize:oriented:` to the segmentation network, its two
///   outputs to `decodeSegmentation...`, then `gateInput` to the gate network;
/// - the print's input (steps 0 to 2): `autoOrient`, the turned crop segmented again when it was turned
///   (the same two calls, `oriented` YES), `makeCanvas`, then `canvasWSQWithBitrate:` and `maskPNG`.
///
/// Not for use from more than one thread at a time.
@interface P5Crop : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// A crop read from an image file's bytes (the test vectors' `input_crop_upright.png`). Nil when it cannot
/// be decoded.
+ (nullable instancetype)cropWithImageData:(NSData *)data NS_SWIFT_NAME(decoded(from:));

@property(nonatomic, readonly) NSInteger width;
@property(nonatomic, readonly) NSInteger height;

/// Step 1, first half: the crop letterboxed onto `size` x `size` for the segmentation network (pad 114,
/// RGB, / 255), as `size * size * 3` float32. `oriented`: the crop step 0 turned, not the crop itself.
/// Empty when there is nothing to segment.
- (NSData *)segmentationInputWithSize:(NSInteger)size oriented:(BOOL)oriented NS_SWIFT_NAME(segmentationInput(size:oriented:));

/// Step 1, second half: the network's two outputs decoded the C2CL way, for the image the last
/// `segmentationInputWithSize:oriented:` with the same `oriented` was made from. `detections` is
/// `rows` x `columns` float32, `prototypes` `height` x `width` x `channels`. NO when no finger is found.
- (BOOL)decodeSegmentationWithDetections:(NSData *)detections
                                    rows:(NSInteger)rows
                                 columns:(NSInteger)columns
                              prototypes:(NSData *)prototypes
                                  height:(NSInteger)height
                                   width:(NSInteger)width
                                channels:(NSInteger)channels
                                oriented:(BOOL)oriented
    NS_SWIFT_NAME(decodeSegmentation(detections:rows:columns:prototypes:height:width:channels:oriented:));

/// Step G: the gate network's input, `[1, 640, 400, 2]` float32 (the grey canvas and its mask, / 255). Nil
/// before the crop has been segmented.
- (nullable NSData *)gateInput;

/// Step 0, auto-orient, on the gate's segmentation: the degrees the crop was turned by, 0 when it was not
/// (it does not lean, or leans past the limit). A crop that was turned has to be segmented again
/// (`oriented` YES) before `makeCanvas`.
- (double)autoOrient;

/// Step 2, the grey canvas: the student network's 400 x 512 input, from the turned crop when step 0 turned
/// it. NO when it cannot be made (a turned crop not segmented yet, or no finger).
- (BOOL)makeCanvas;

/// The canvas as WSQ at 500 ppi. `bitrate` is kept to 0.75 ... 4.0 (2.25 when it is not a number). Nil when
/// there is no canvas or it cannot be encoded.
- (nullable NSData *)canvasWSQWithBitrate:(float)bitrate NS_SWIFT_NAME(canvasWSQ(bitrate:));

/// The finger's soft mask before placing (the reference's `csoft`), as a lossless PNG.
- (nullable NSData *)maskPNG;

/// The crop itself as a PNG (request schema 1).
- (nullable NSData *)cropPNG;

/// One of the gate's pictures as a PNG, grey in every channel. Nil when it has not been made.
- (nullable NSData *)debugPNG:(P5DebugImage)image NS_SWIFT_NAME(debugPNG(_:));

/// The crop's sharpness: the variance of its Laplacian. 0 when it cannot be measured.
- (double)sharpness;

@end

/// A camera frame turned upright, as the screen shows it: what the fingers are found on and cut from.
@interface P5Frame : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// From a BGRA buffer as the back camera delivers it, in the sensor's landscape (a video frame, or an
/// uncompressed still): turned a quarter clockwise. Nil for any other pixel format.
+ (nullable instancetype)frameWithPixelBuffer:(CVPixelBufferRef)pixelBuffer NS_SWIFT_NAME(upright(pixelBuffer:));

/// From a decoded still, its pixels in the sensor's landscape as the camera stores them: turned a quarter
/// clockwise.
+ (nullable instancetype)frameWithCGImage:(CGImageRef)image NS_SWIFT_NAME(upright(cgImage:));

@property(nonatomic, readonly) NSInteger width;
@property(nonatomic, readonly) NSInteger height;

/// The whole frame letterboxed onto `size` x `size` for the finger detector, as Android feeds it a still
/// (aspect kept, pad 114, RGB, / 255): `size * size * 3` float32.
- (NSData *)detectorInputWithSize:(NSInteger)size NS_SWIFT_NAME(detectorInput(size:));

/// A detector box on that letterboxed input, as fractions of it (0 to 1), in this frame's pixels.
- (CGRect)frameRectForDetectorRect:(CGRect)rect inputSize:(NSInteger)size NS_SWIFT_NAME(frameRect(forDetectorRect:inputSize:));

/// One finger: `box` cut from the frame (kept inside it), resampled by `factor` onto 500 ppi (area
/// averaging when shrinking, cubic when enlarging, as it is within half a percent of 1), then turned
/// `turns` quarter-turns clockwise so the fingertip points up. Nil for an empty box.
- (nullable P5Crop *)cropAt:(CGRect)box resample:(double)factor quarterTurnsClockwise:(NSInteger)turns
    NS_SWIFT_NAME(crop(at:resample:quarterTurnsClockwise:));

@end

NS_ASSUME_NONNULL_END
