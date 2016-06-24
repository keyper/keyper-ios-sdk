#import <Foundation/Foundation.h>
#import "KEYSDKConstants.h"

@class KEYSDKConfiguration;
@class KEYPushNotificationRecommendedHostAppAction;

// If you have questions or need
@interface KEYSDK : NSObject

@property (copy, nonatomic, readonly) KEYSDKConfiguration *configuration;
@property (strong, nonatomic, readonly) NSBundle *stringsBundle;

+ (KEYSDK *)sharedSDK;

// Configures keyper SDK - required before using any other class in keyper SDK.
//
// If you need to make parameter changes at runtime, call configure:
// again, call resetViews, and get a new instance of the root navigation controller if required.
// Some parameter changes done via configure: are reflected in the already-running
// views though (e.g., apiBaseURL).
+ (void)configure:(void (^)(KEYSDKConfiguration *))configuration;

// Authentication
+ (void)authenticateWithRouteIdentifier:(NSString *)routeIdentifier hostAppToken:(NSString *)hostAppToken resultBlock:(void (^)(NSError *error))resultBlock;
+ (void)logout;
+ (void)setDeviceTokenForPushNotifications:(NSData *)deviceToken;

// Showing the SDK. ticketsRootViewController is always contained in rootNavigationController, and vice versa.
// Ideally, you would just add rootNavigationController to your view hierarchy (e.g. tab bar or side menu),
// and only access ticketsRootViewController for customization purposes (e.g. to set customTitleView).
@property (strong, nonatomic, readonly) UINavigationController *rootNavigationController;
@property (strong, nonatomic, readonly) UIViewController *ticketsRootViewController;

// Reset both the rootNavigationController and ticketsRootViewController. After calling this,
// re-add rootNavigationController in your view hierarchy.
- (void)resetViews;

// Push Notifications
+ (KEYPushNotificationRecommendedHostAppAction *)recommendedHostAppActionWithNotification:(NSDictionary *)remoteNotification;
- (void)handleRemoteNotification:(NSDictionary *)remoteNotification;

@end
