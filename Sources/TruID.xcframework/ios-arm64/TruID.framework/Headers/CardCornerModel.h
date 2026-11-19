//
//  CardCornerModel.h
//  TruID
//

#import <CoreGraphics/CoreGraphics.h>
#import <CoreVideo/CoreVideo.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// One pass of a card corner model: the card's corners, clockwise from the top-left, in the pixels of the
/// image the model ran on, and how sure the model is of them.
@interface CardCorners : NSObject

@property(nonatomic, readonly) CGPoint topLeft;
@property(nonatomic, readonly) CGPoint topRight;
@property(nonatomic, readonly) CGPoint bottomRight;
@property(nonatomic, readonly) CGPoint bottomLeft;
/// The live model's objectness, or the heatmap model's mean peak over the four corners.
@property(nonatomic, readonly) float confidence;

@end

/// The Android SDK's card corner models (DocAligner, `CardDetector`), run with ONNX Runtime as Android runs
/// them. Both take the whole image squeezed to 256x256, RGB scaled to [0, 1], and give corners clockwise
/// from the top-left.
///
/// - The live model (lcnet050, point regression): four corners and an objectness, for every frame.
/// - The precise model (lcnet100, heatmaps): four 128x128 heatmaps, one per corner, decoded to a peak with a
///   sub-pixel centroid around it. Slower, and more exact; run once, on the frame picked for upload.
///
/// Not for use from more than one thread at a time.
@interface CardCornerModel : NSObject

/// Both models, decoded from their base64 sources into ONNX Runtime sessions. Nil, with `error` set, when
/// either cannot be loaded.
+ (nullable instancetype)loadedWithError:(NSError **)error;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The live model on an upright BGRA camera frame. Always gives its corners, whatever the objectness; nil
/// only when the model could not be run.
- (nullable CardCorners *)detectLiveIn:(CVPixelBufferRef)pixelBuffer NS_SWIFT_NAME(detectLive(in:));

/// The precise model on an upright image. Nil only when the model could not be run.
- (nullable CardCorners *)detectPreciseIn:(CGImageRef)image NS_SWIFT_NAME(detectPrecise(in:));

@end

NS_ASSUME_NONNULL_END
