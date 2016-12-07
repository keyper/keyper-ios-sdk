#import <Foundation/Foundation.h>
#import "KEYSDKConstants.h"

@class KEYSDKConfiguration;
@class KEYPushNotificationRecommendedHostAppAction;

// Extensive Readme at https://github.com/keyper/keyper-ios-sdk
@interface KEYSDK : NSObject

// Singleton
+ (KEYSDK *)sharedSDK;

@property (copy, nonatomic, readonly) KEYSDKConfiguration *configuration;
@property (strong, nonatomic, readonly) NSBundle *stringsBundle;

// Showing the SDK. ticketsRootViewController is always contained in rootNavigationController, and vice versa.
// Ideally, you would just add rootNavigationController to your view hierarchy (e.g. tab bar or side menu),
// and only access ticketsRootViewController for customization purposes (e.g. to set customTitleView).
@property (strong, nonatomic, readonly) UINavigationController *rootNavigationController;
@property (strong, nonatomic, readonly) UIViewController *ticketsRootViewController;

// Configures keyper SDK - required before using any other class in keyper SDK.
//
// If you need to make parameter changes at runtime, call configure:
// again, call resetViews, and get a new instance of the root navigation controller if required.
// Some parameter changes done via configure: are reflected in the already-running
// views though (e.g., apiBaseURL).
- (void)configure:(void (^)(KEYSDKConfiguration *))configuration;

// Authentication
- (void)authenticateWithRouteIdentifier:(NSString *)routeIdentifier hostAppToken:(NSString *)hostAppToken resultBlock:(void (^)(NSError *error))resultBlock;
- (BOOL)isAuthenticated;
- (void)logout;
- (void)setDeviceTokenForPushNotifications:(NSData *)deviceToken;

// Reset both the rootNavigationController and ticketsRootViewController. After calling this,
// re-add rootNavigationController in your view hierarchy.
- (void)resetViews;

// Push Notifications
- (KEYPushNotificationRecommendedHostAppAction *)recommendedHostAppActionWithNotification:(NSDictionary *)remoteNotification;
- (void)handleRemoteNotification:(NSDictionary *)remoteNotification;


// Deep Linking with Branch.io
// Call this when a deep link arrives that must be handled by keyper SDK.
// You can find out whether it has to be handled by using isKeyperDeepLink:;
- (void)handleDeepLink:(NSDictionary *)params error:(NSError *)error;
- (BOOL)isKeyperDeepLink:(NSDictionary *)params;

@end
