//
//  WSQWrapper.h
//  TruID
//
//  Created by truID on 23/05/2024.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN


@interface FingerJet : NSObject

+ (NSData *)encodeISOFromImage:(UIImage *)image;
	
@end

NS_ASSUME_NONNULL_END
