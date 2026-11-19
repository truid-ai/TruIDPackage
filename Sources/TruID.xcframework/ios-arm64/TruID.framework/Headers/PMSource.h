//
//  PMSource.h
//  TruID
//
//  Created by truID on 12/09/2024.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PMSource : NSObject

/// The model's bytes, read in place from the TruID binary (`EmbeddedModels/pm.tflite`, section `__tm_pm`).
/// Nil when that section is missing from the build.
@property(nonatomic, readonly, nullable) NSData *model;

@end

NS_ASSUME_NONNULL_END
