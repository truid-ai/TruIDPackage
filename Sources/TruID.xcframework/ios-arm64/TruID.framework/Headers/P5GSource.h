//
//  P5GSource.h
//  TruID
//
//  Pipeline P5's NFIQ2 gate (the C2CL package's nfiq2_gate_v1st, gate update 1.3.2).
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface P5GSource : NSObject

/// The model's bytes, read in place from the TruID binary (`EmbeddedModels/p5g.tflite`, section `__tm_p5g`).
/// Nil when that section is missing from the build.
@property(nonatomic, readonly, nullable) NSData *model;

@end

NS_ASSUME_NONNULL_END
