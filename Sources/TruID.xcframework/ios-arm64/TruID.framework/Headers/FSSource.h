//
//  FSSource.h
//  TruID
//
//  The fingertip segmentation network pipeline P5 reads (the Android SDK's fingerseg.tflite, yolo26n-seg).
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FSSource : NSObject

/// The model's bytes, read in place from the TruID binary (`EmbeddedModels/fs.tflite`, section `__tm_fs`).
/// Nil when that section is missing from the build.
@property(nonatomic, readonly, nullable) NSData *model;

@end

NS_ASSUME_NONNULL_END
