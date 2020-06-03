#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "KEYSDKConstants.h"

@class KEYSDKConfiguration;
@class KEYPushNotificationRecommendedHostAppAction;
@class KEYTicketOffersCount;

// Extensive Readme at https://github.com/keyper/keyper-ios-sdk
@interface KEYSDK : NSObject

// Singleton
+ (nonnull KEYSDK *)sharedSDK;

@property (copy, nonatomic, readonly, nullable) KEYSDKConfiguration *configuration;
@property (strong, nonatomic, readonly, nonnull) NSBundle *stringsBundle;

// Showing the SDK. ticketsRootViewController is always contained in rootNavigationController, and vice versa.
// Ideally, you would just add rootNavigationController to your view hierarchy (e.g. tab bar or side menu),
// and only access ticketsRootViewController for customization purposes (e.g. to set customTitleView).
// You can also use just ticketsRootViewController, and insert it directly into your own UINavigationController.
// In this case, the rootNavigationController is still instantiated, but will remain unused.
@property (strong, nonatomic, readonly, nonnull) UINavigationController *rootNavigationController;
@property (strong, nonatomic, readonly, nonnull) UIViewController *ticketsRootViewController;

// The number of ticket offers which require a user action. This property is Key-Value-Observing (KVO) compliant, so
// you can subscribe to updates easily:
// https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/KeyValueObserving/KeyValueObserving.html
//
// We think that `ticketOffersCount.incomingPendingOffersCount + ticketOffersCount.outgoingPendingOffersCount`
// is the ideal number to show to the user. The SDK internally uses this metric to show the pending indicator
// in the tickets view if any offers are pending.
@property (strong, nonatomic, readonly, nullable) KEYTicketOffersCount *ticketOffersCount;

// Configures keyper SDK - required before using any other class in keyper SDK.
//
// If you need to make parameter changes at runtime, call configure:
// again, call resetViews, and get a new instance of the root navigation controller if required.
// Some parameter changes done via configure: are reflected in the already-running
// views though (e.g., apiBaseURL).
- (void)configure:(void (^_Nonnull)(KEYSDKConfiguration *_Nonnull))configuration;

// Authentication. It is MOST likely that you don't need to set any meaningful value
// for scopeID - you can just pass 0.
- (void)authenticateWithRouteIdentifier:(nonnull NSString *)routeIdentifier hostAppToken:(nonnull NSString *)hostAppToken scopeID:(NSInteger)scopeID resultBlock:(void (^_Nullable)(NSError *_Nullable error))resultBlock;
- (BOOL)isAuthenticated;
- (nullable NSString *)authenticatedUserEmail;
- (nullable NSString *)authenticatedUserId;
- (void)logout;
- (void)setDeviceTokenForPushNotifications:(nonnull NSData *)deviceToken;
- (void)getMyTicketsPushNotificationsStatusWithResultBlock:(void (^_Nonnull)(KEYMyTicketsPushNotificationsStatus))resultBlock;
- (void)setMyTicketsPushNotificationsEnabled:(BOOL)enabled;

// Reset both the rootNavigationController and ticketsRootViewController. After calling this,
// re-add rootNavigationController in your view hierarchy.
- (void)resetViews;

// Push Notifications
- (nonnull KEYPushNotificationRecommendedHostAppAction *)recommendedHostAppActionWithNotification:(nonnull NSDictionary *)remoteNotification;

// This will handle a push notification within the SDK. E.g. if a ticket offer arrived,
// the SDK will reload the ticket offers view and switch the tickets view segmented control
// to the offers view.
// Before calling this, make sure that recommendedHostAppActionWithNotification: does not
// return KEYNotificationRecommendedHostAppActionDoNothing.
//
// navigateToChangedView: If YES, the SDK will switch to the view that this notification affected
// the most. E.g. if a ticket offer arrives, it will show the ticket offers list view.
// If using UNNotificationCenter, you will likely want to pass
// FALSE in userNotificationCenter(_, willPresent:, withCompletionHandler:) and
// TRUE in userNotificationCenter(_, didReceive, withCompletionHandler:). This way, the SDK
// will only navigate to a changed view (e.g. ticket offers) if the app is currently in background or closed.
// If the app is active, you might not want to let the keyper SDK change the view hierarchy as this would be
// a bit unsettling for the user.
- (void)handleRemoteNotification:(nonnull NSDictionary *)remoteNotification navigateToChangedView:(BOOL)navigateToChangedView;

// DEPRECATED - use handleRemoteNotification:navigateToChangedView instead!
- (void)handleRemoteNotification:(nonnull NSDictionary *)remoteNotification __deprecated;

// Deep Linking with Branch.io
// Call this when a deep link arrives that must be handled by keyper SDK.
// You can find out whether it has to be handled by using isKeyperDeepLink:;
- (void)handleDeepLink:(nonnull NSDictionary *)params error:(NSError *_Nullable)error;
- (BOOL)isKeyperDeepLink:(nonnull NSDictionary *)params;

@end
