//
//  FingerprintProcessor.h
//  TruID
//
//  Created by truid on 16/07/2026.
//

#import <UIKit/UIKit.h>

@interface FingerprintProcessor : NSObject

/**
 Processes a raw fingerprint image, orienting, normalizing, and masking it.
 @param inputImage The raw UIImage to process.
 @return A processed UIImage with black ridges on a white background, or nil if an error occurs.
 */
+ (UIImage *)processImage:(UIImage *)inputImage;

@end
