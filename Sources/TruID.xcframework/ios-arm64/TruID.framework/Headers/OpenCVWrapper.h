//
//  OpenCVWrapper.h
//  TruID
//
//  Created by truID on 14/05/2024.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface OpenCVWrapper : NSObject
+ (NSString *)getOpenCVVersion;
+ (UIImage *)grayscaleImg:(UIImage *)image;
+ (UIImage *)convertToRGBFromGrayscale:(UIImage *)image;
+ (UIImage *)resizeImg:(UIImage *)image
                      :(int)width
                      :(int)height
                      :(int)interpolation;
+ (UIImage *)binarize:(UIImage *)image;
+ (UIImage *)applyPill:(UIImage *)image :(UIImage *)pillImage;
+ (BOOL)isImageOverexposed:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
