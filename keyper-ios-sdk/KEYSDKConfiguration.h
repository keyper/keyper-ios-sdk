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
@property (nonatomic, copy) NSURL *apiBaseURL; // required
@property (nonatomic, copy) NSString *appSecret; // required
@property (nonatomic, assign) BOOL enableSSLCertificatePinning; // only works for keyper's production server environment; make sure to update keyper SDK often if you set to YES; else, set to NO
@property (nonatomic, assign) BOOL allowInvalidSSLCertificates; // set YES only for debugging purposes; strongly discouraged for production use!

// Deep linking
@property (nonatomic, assign) BOOL enableBranchDeepLinking; // ignored if Branch is not used
@property (nonatomic, assign) BOOL allowDeepLinkingToDismissAnyModalView; // any of the app's modal views (presentViewController:animated:completion:) are dismissed when a ticket transfer is processed by keyper SDK

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
