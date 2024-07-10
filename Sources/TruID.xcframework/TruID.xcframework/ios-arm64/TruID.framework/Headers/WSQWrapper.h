//
//  WSQWrapper.h
//  TruID
//
//  Created by truID on 23/05/2024.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

// Definition of image_data_t structure
typedef struct image_data {
    int width;
    int height;
    int ppi;
    int* pixels;
} image_data_t;

@interface WSQWrapper : NSObject

// Decodes WSQ image data from a file path
+ (UIImage *)decodeWSQFromFile:(NSString *)filePath;

// Decodes WSQ image data from a byte array
+ (UIImage *)decodeWSQFromData:(NSData *)data;

// Encodes an image to WSQ format with given bitrate and PPI
+ (NSData *)encodeWSQFromImage:(UIImage *)image bitrate:(float)bitrate ppi:(int)ppi comment:(NSString *)comment;

@end

NS_ASSUME_NONNULL_END
