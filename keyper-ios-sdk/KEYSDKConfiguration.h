//
//  KEYSDKConfiguration.h
//  Pods
//
//  Created by Manuel Maly on 19.05.16.
//
//

#import <Foundation/Foundation.h>

@interface KEYSDKConfiguration : NSObject<NSCoding, NSCopying>

// Server configuration
@property (nonatomic, copy) NSURL *apiBaseURL;
@property (nonatomic, assign) BOOL enableSSLCertificatePinning; // only works for production server environment; else, set to NO

// Look and Feel
@property (nonatomic, copy) UIColor *tintColor;
@property (nonatomic, copy) UIColor *navigationBarTintColor;
@property (nonatomic, copy) UIColor *navigationBarTextColor;
@property (nonatomic, copy) UIFont *navigationBarFont; // font size will be adapted to ~ match default look and feel
@property (nonatomic, copy) UIImage *sendTicketsBadgeImage; // shown in "send tickets" screen for platform friends
@property (nonatomic, assign) CGFloat bottomInset; // used to inset views at the bottom (e.g. when displaying SDK with a UITabbar)

// Debugging
@property (nonatomic, assign) BOOL showServerErrorsAsAlerts;
@property (nonatomic, assign) BOOL enableAFNetworkingLogger;

@end


@interface KEYSDKConfiguration (Convenience)

- (UIColor *)darkenedTintColor;

@end