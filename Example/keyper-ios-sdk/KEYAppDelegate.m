//
//  KEYAppDelegate.m
//  keyper-ios-sdk
//
//  Created by Manuel Maly on 06/24/2016.
//  Copyright (c) 2016 Manuel Maly. All rights reserved.
//

#import "KEYAppDelegate.h"
#import "Branch.h"
#import "KEYSDK.h"
#import "KEYSDKConfiguration.h"
#import "KEYPushNotificationRecommendedHostAppAction.h"

@implementation KEYAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{

    // Configure most important properties in keyper SDK. We will call configure: again in
    // KEYViewController.m, but this is not necessary; you could just do it all at once
    // in here.
    [KEYSDK.sharedSDK configure:^(KEYSDKConfiguration *c) {
        c.apiBaseURL = [NSURL URLWithString:@"https://develop.api.keyper.io/api/"];
        c.enableSSLCertificatePinning = NO;
    }];

    // Only configure branch.io once per runtime
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        [[Branch getInstance] initSessionWithLaunchOptions:launchOptions andRegisterDeepLinkHandler:^(NSDictionary *_Nonnull params, NSError *_Nullable error) {
            // Let keyper SDK handle deep link if the SDK recognizes it as such
            if ([[KEYSDK sharedSDK] isKeyperDeepLink:params]) {
                [[KEYSDK sharedSDK] handleDeepLink:params error:error];
            }
        }];
    });

    [self requestPushNotifications];

    return YES;
}

- (void)requestPushNotifications {
    UIApplication *application = [UIApplication sharedApplication];

    UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert | UIUserNotificationTypeBadge | UIUserNotificationTypeSound categories:nil];
    [application registerUserNotificationSettings:settings];
}

- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings {
    [application registerForRemoteNotifications];
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)remoteNotification fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler {

    switch (application.applicationState) {
        case UIApplicationStateInactive: {
            // The user has put the app in background, but not yet killed it.
            // She clicked or swiped the notification and the app now opens.
            KEYPushNotificationRecommendedHostAppAction *recommendedAction = [KEYSDK.sharedSDK recommendedHostAppActionWithNotification:remoteNotification];

            if (recommendedAction.letSDKHandleNotification) {
                // This will be executed if keyper SDK
                [[KEYSDK sharedSDK] handleRemoteNotification:remoteNotification];
            }

            if (recommendedAction.showSDKRootNavigationController) {
                // Insert code here that shows the keyper SDK's view (rootNavigationController) now
            }

            if (recommendedAction.authenticateSDK) {
                // Authenticate keyper SDK if appropriate. This will be executed if keyper SDK did not find any active credential data.
            }

            completionHandler(UIBackgroundFetchResultNewData);
            break;
        }
        default:
            // App is either open or in backgrounding mode (i.e. the system wakes the app for a short time)
            // The user did not click or swipe the notification, so we don't need to switch views.
            // Handle with your own logic if necessary.
            break;
    }
}

- (void)application:(UIApplication *)app didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {

    // Setup push notifications handling in keyper SDK
    [KEYSDK.sharedSDK setDeviceTokenForPushNotifications:deviceToken];
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {

    // Let branch.io handle incoming URLs (< iOS 10)
    BOOL handled = [[Branch getInstance] handleDeepLink:url];

    return handled;
}

- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray *_Nullable))restorationHandler {

    // Let branch.io handle incoming URLs (iOS 10+)
    BOOL handled = [[Branch getInstance] continueUserActivity:userActivity];

    return handled;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
