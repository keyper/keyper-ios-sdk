 # Keyper iOS SDK Developers Guide
**SDK Version: 1.1.0**
 
Contact: *dev@keyper.io*

Last Updated: *27 July 2018*

The keyper SDK offers developers a complete mobile ticket solution, that they can include and use within their apps.

## Changelog

**2016-06-29**

Initial release

**2016-12-09**

v0.9.1

- Adding support for handling season tickets, and even sending them individually
- Using request batching (with https://github.com/keyper/KEYBatchRequest)
- Added deep linking
- Improving semantics, like price/currency homogeneity
- Refining language when addressing the user
- Fixing some bugs

**2017-05-31**

v0.9.2

- Adding required appSecreat as KEYConfiguration parameter
- Improved ticket card view, adding sales type at the bottom of tickets that support it
- Bug fixes and improvements

**2017-06-20**

v0.9.3

- Adding automatic polling and refreshing for pending tickets (whose barcode is still being generated)
- Turning the device's screen to max brightness when viewing an old/expired barcode 

**2017-07-03**

v0.9.4

- Possibly fixing bug where host app does not react to choosing a phone or email address when sending a ticket 
- Removing existing data of table views when logging out and in again (if user id changes)
- Preventing multiple entries for contacts with multiple linked entries (e.g. for records from Facebook or Google)
- Improve messaging when user tries to send tickets that have not yet been loaded
- Possibly fixing problem that ticket actions are not correctly updated if the new data has no ticket actions contained
- Greying out send-tickets button if tickets are not sendable

**2017-07-21**

v1.0.0

- Adding configuration parameter `showAlertOnExpiredKeyperToken`
- Fixing bugs related to order partner updates and barcode polling
- Improving UX via slight adaptions and text changes
- Fixing problem of redundant calls after each logout/login process
- Fixing a bug that lead to a logout race condition
- Logging off the user for _every_ call that returns an unauthorized response (401)

**2017-07-24**

v1.0.1

- Fixing a bug where a login/logout loop happened in certain scenarios through a race condition
- Fixing ticket-selector bugs when choosing tickets out of a season ticket

**2017-08-02**

v1.0.2

- Adding new internal ticket condition states "used" and "in commission"
- Fixing bugs when selecting tickets when sending a season ticket
- Fixing a bug that prevented tickets from being shown correctly transitioning from a pending state to a correct state

**2017-09-07**

v1.0.3

- Adding new ticket type: packages (i.e. season tickets with multiple barcodes)
- Adding events list for season tickets (in "Info" tab)
- Adding ticket count to tickets selection when sending a season ticket as single tickets

**2017-09-27**

v1.0.4

- Fixing issues in iOS 11 and on iPhone X.

**2018-07-27**

v1.1.0

- Now bundled into a framework instead of only a static library
- The pod name has changed to `keyperSDK` (instead of `keyper-ios-sdk`) - please update all your import statements and perform a clean (CMD+Shift+K)! The reason for the rename is that the dashes in the old name were translated to underscores, and we suspected issues with the framework integration because of that. The other instances of `keyper-ios-sdk` (github repo URL, bundle file names,...) stay unchanged for now to avoid more breaking changes.
- Adding possibility to enable/disable "my ticket" notifications (`setMyTicketsPushNotificationsEnabled` and `getMyTicketsPushNotificationsStatusWithResultBlock` in `KEYSDK`)
- Adding possibility to let the keyper SDK navigate to affected views as a reaction to a push notification, via
`handleRemoteNotification:navigateToChangedView:`; `handleRemoteNotification:` is therefore now deprecated
- Adding possibility for you to track the pending tickets count (`ticketOffersCount`) to e.g. show the number in a `UITabBar` badge.
- New indicator (like a badge without a number) in tickets view if any offers are pending
- Migrating to view-controller based status bar appearance
- Fixing an instance of inappropriate default color (Done button when ticket recipients while sending a ticket)
- Fixing remaining cosmetic issues when starting the SDK repeatedly with different color configurations
- Improving ticket detail info view for the case when no upcoming event is available
- Fixing some UIKit accesses that happened off-main-thread
- Removing Example app because it was heavily outdated


## Getting Started

There are at least two ways to integrate the SDK: with or without Cocoapods. We will show both ways here.

### Prerequisites

- This SDK has been built with Xcode 9.4, so we'd recommend you use at least this version.
- If you decide to use Cocoapods, you need to use version 1.0.0 or higher (check with ```pod --version```), since the podspec is not compabible with lower versions.
- The SDK does not use any Swift code, so you need not worry about runtime versions. 

### Adding SDK Binaries WITH Cocopoapods

1. Open Terminal.app
2. Update/install Cocoapods by running ```sudo gem install cocoapods```
3. ```cd``` into your project directory (such that ```ls``` shows the ```.xcodeproj``` file)
4. If your project is not yet using Cocoapods:
    1. Run ```pod init```
    2. Open the newly created ```Podfile``` (e.g. with ```nano Podfile```, or ```open .``` and then opening it from Finder)
    3. In the ```Podfile```, uncomment or edit your minimal target platform (e.g. ```platform :ios, '9.0'```). keyper SDK supports versions as low as 8.0.
5. In the ```Podfile```, add the target(s) and keyper SDK dependency for your project (named exactly like the one from Xcode when you look at the project file), like so: 
    
	```
	target 'target-name-that-you-copied-from-xcode' do 
      pod 'keyperSDK', :git => 'https://github.com/keyper/keyper-ios-sdk.git', :tag => '1.1.0'
	end
	```
	Look at this repository's branch selector to find out which versions are available. Each version has its own branch. Later on, the SDK might be available via Cocoapod's central repository, but currently it's not.
6. Run ```pod install```. This might take a while when executed the first time.
7. Open the project in Xcode using the ```.xcworkspace``` file from this time on. If your original workspace (before integrating Cocoapods) relied on subprojects, have a look at Cocoapods' documentation to let Cocoapods generate your workspace file properly (especially https://guides.cocoapods.org/syntax/podfile.html#project).

### Adding SDK Binaries WITHOUT Cocopoapods

1. Download and unzip the SDK's files (e.g., for version 1.1.0, the complete ZIP file can be found at https://github.com/keyper/keyper-ios-sdk/archive/1.1.0.zip - look at this repository's branch/tag selector to find out which versions are available).
2. Create a ```keyper SDK```, ```Vendor``` or similar group in your Xcode project if you don't want the SDK's files to clutter your structure
3. Locate the framework within the previously extracted files, and drag it into your project (into a group if you want). You might also have to drag it into project settings > Target > General > Embedded binaries, and into Build Phases > Link Binary with Libraries.

If you run into any problems with installation, please contact us at *dev@keyper.io*.

## General

keyper iOS SDK is compatible with deployment targets of 8.0 or higher.

The SDK consists of:

- A .framework folder, and within this:
- Header files (*.h) that allow you to start and interface with the SDK in your code.
- A static library (`keyperSDK`) that contains all the views and business logic of the SDK in compiled form. Note that this file is way bigger than the actual size impact the SDK will have on your app.
- Bundle files (*.bundle) that contain image and localization assets. You can look into them by right-clicking in Finder and selecting "Show package contents".

The SDK requests calendar, camera, contacts, and photo library permissions at runtime - therefore, please add these to your app target's Info.plist file:

```
    <key>NSCalendarsUsageDescription</key>
    <string>Calendar access for storing event dates.</string>
    <key>NSCameraUsageDescription</key>
    <string>Camera access for scanning ticket barcodes.</string>
    <key>NSContactsUsageDescription</key>
    <string>Accessing Contacts for choosing ticket recipients</string>
    <key>NSPhotoLibraryUsageDescription</key>
    <string>Photo library access for barcode scanning.</string>
```
 
## Localization/Language

You need to setup the localizations that you want the SDK to show within your project. Currently, keyper SDK supports English and German (en & de). Go to your project file, select the project in the left pane at the top, and look at the "Localizations" section. E.g. if you only have an "English" item in this section, then the SDK will be in English only.

## Development
The SDK consists of a singleton instance (```[KEYSDK sharedSDK]```) that exposes some helper methods and a few classes, that help you integrate a complete mobile ticket solution to your app.

### Initialize & Configure

To initialize and configure the SDK, you can use the following snippet in your app (ideally in the very first line of ```application:didFinishLaunchingWithOptions:``` in the app delegate):

```
    [KEYSDK.sharedSDK configure:^(KEYSDKConfiguration *c) {
    	// This line can be omitted, then the apiBaseURL will default to keyper's production server
        c.apiBaseURL = [NSURL URLWithString:@"https://sandbox.api.keyper.io/api/"];
    }];
```        

You can always get a reference to the SDK's singleton object by calling:

```
[KEYSDK sharedSDK]
```

### Login

Once you have the SDK configured, you can connect a user of your app with the keyper service. To do so, you have to configure your keyper b2b account in the keyper [b2b web app](https://app.keyper.io/b2b.html#) or the keyper [b2b sandbox webapp](https://sandbox.app.keyper.io/b2b.html#).

There you can configure a route identifier, which you will need in order to oauth with the keyper service.

In order to authenticate the user against the keyper service, use the following code snippet:

```
[KEYSDK.sharedSDK authenticateWithRouteIdentifier:@"keyper" hostAppToken:@"userTokenOfHostApp" resultBlock:nil];
```

or include a callback that lets you react to when the authentication finishes or fails:

```
[KEYSDK.sharedSDK authenticateWithRouteIdentifier:@"keyper" hostAppToken:@"userTokenOfHostApp" resultBlock:^(NSError *error) {
  // Do something. error will be nil if authentication is successful.
}];
```

The route identifier is configured in the b2b web app. The host app token is the session token of your user.

Once you have authenticated your user, you can present the user with the mobile ticket part of the SDK. You can even show this UI part before authentication is finished - a loading indicator will be shown until all requests have completed (tickets and orders calls will run after authentication finished).

If you are not sure if the SDK is authenticated, you can use the following helper method.

```
[KEYSDK.sharedSDK isAuthenticated];
```

### Display The Mobile Ticket Area

In order to display the mobile ticket area, the easiest way is to just show ```rootNavigationController```:

```
[self presentViewController:KEYSDK.sharedSDK.rootNavigationController animated:YES completion:nil];
```

If your app has a side menu drawer, you could just add ```KEYSDK.sharedSDK.rootNavigationController``` to your side menu as centerViewController (or however it's called); or if you use a ```UITabBarController```, you would add ```KEYSDK.sharedSDK.rootNavigationController``` as part of its ```viewControllers``` array. 

Alternatively, you can configure ```ticketsRootViewController``` and then show ```rootNavigationController```:

```
// Get the SDK's single instance of the root view controller:
UIViewController *vc = KEYSDK.sharedSDK.ticketsRootViewController;

// Setup vc as required, e.g. here we add a bar button:
vc.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(onDoneTapped)];

// Present the navigation controller, which already has ticketsRootViewController as its only view controller set:
[self presentViewController:KEYSDK.sharedSDK.rootNavigationController animated:YES completion:nil];
```

Note that both ```rootNavigationController``` and ```ticketsRootViewController``` are both instantiated lazily on first access to __any of them__. Once they are instantiated, both are kept as single instances until you call ```[KEYSDK.sharedSDK resetViews]```.

**Authentication scenarios:**

Your app can authenticate right when it starts, or just at the time when it shows ```rootNavigationController``` or ```ticketsRootViewController```. It is even possible to defer authentication a bit; the views will just display a loading indicator until authentication has finished.

- If the SDK is authenticated, tickets and offers are loaded and shown.
- If the SDK is not yet authenticated at the time of showing the UI, or you have called ```[KEYSDK.sharedSDK logout]```, then the mobile ticket area will display no tickets, but a loading indicator at the top. This is because the views wait for a successful authentication via ```authenticateWithRouteIdentifier:hostAppToken:resultBlock:```, after which they will properly reload and show the tickets.
- If the SDK has an old or invalid token from a previous session, the mobile ticket area will display a user-dismissible error message; however, again, the views will properly reload and show the tickets after another successful authentication via ```authenticateWithRouteIdentifier:hostAppToken:resultBlock:```.

### Logout

If you want to clear SDK data from the device (e.g. when you logout your user), you can use the following method to do so:

```
[KEYSDK.sharedSDK logout];
```

The logout method will clear the keyper user session and all related data from the device as well as unsubscribe the device from keyper push notifications (if they were configured).

### Push Notifications

To register for remote push notifications (if your app not already does), add this code to the App Delegate:

```
- (void)requestPushNotifications {
    UIApplication *application = [UIApplication sharedApplication];

    UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert | UIUserNotificationTypeBadge | UIUserNotificationTypeSound categories:nil];
    [application registerUserNotificationSettings:settings];
}

- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings {
    [application registerForRemoteNotifications];
}
```

Call `requestPushNotifications` as soon as possible (e.g. after the user has logged into your app, or even right at app start).

If you want to let keyper servers send push notifications to your app (please talk to our support about that: dev@keyper.io), also add this code in the App Delegate:

```
- (void)application:(UIApplication *)app didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {

    // Put your own configuration here if necessary

    [KEYSDK.sharedSDK setDeviceTokenForPushNotifications:deviceToken];
}
```

The actual notification handling is done with the following code. Note that this is not yet adapted to the new iOS 10 notification APIs - the iOS 9 APIs still work fine though.

```
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)remoteNotification fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler {

    switch (application.applicationState) {
        case UIApplicationStateInactive:
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
        default:
            // App is either open or in backgrounding mode (i.e. the system wakes the app for a short time)
            // The user did not click or swipe the notification, so we don't need to switch views.
            // Handle with your own logic if necessary.
            break;
    }
}
```

### Deep Linking

keyper features a tight integration with branch.io's deep linking framework. To setup deep linking in your app, please follow these steps:

**1. Add your app's branch key to each relevant target's Info.plist file:**

```
<key>branch_key</key>
<dict>
    <key>live</key>
    <string>key_<YOUR_KEY_HERE></string>
</dict>
```

**2. In the App Delegate, beneath the configuration code for the keyper SDK, setup Branch's deep link handling:**

```
static dispatch_once_t onceToken;
dispatch_once(&onceToken, ^{
    [[Branch getInstance] initSessionWithLaunchOptions:launchOptions andRegisterDeepLinkHandler:^(NSDictionary *_Nonnull params, NSError *_Nullable error) {
        // Let keyper SDK handle deep link if the SDK recognizes it as such
        if ([[KEYSDK sharedSDK] isKeyperDeepLink:params]) {
            [[KEYSDK sharedSDK] handleDeepLink:params error:error];
        }
    }];
});
```

You will also need to `#import "Branch.h"` or `@import Branch;`.

**3. Finally, forward URLs that are opened in your app to Branch:**

```
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {

    // Let branch.io handle incoming URLs (< iOS 10)
    BOOL handled = [[Branch getInstance] handleDeepLink:url];

    return handled;
}

// ...

- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray *_Nullable))restorationHandler {

    // Let branch.io handle incoming URLs (iOS 10+)
    BOOL handled = [[Branch getInstance] continueUserActivity:userActivity];

    return handled;
}
```


### Notifications

If you want your users to obtain keyper push notifications, e.g. when they get a new ticket offer, or a new friend request, then you have to take the following actions.

**1. Submit the device token to the SDK every time it changes:**

```
// In AppDelegate:
- (void)application:(UIApplication *)app didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
	
	// Your app's own token handling logic
	// ...
	
    [KEYSDK.sharedSDK setDeviceTokenForPushNotifications:deviceToken];
}
```

**2. In order to allow keyper SDK to handle the received notificaitons, you have to propagate them to the SDK.** 

The SDK offers you a few helper methods to help you do that.  
Once you receive a notification, you can inspect and act on the notification like so:

```
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)remoteNotification fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler {
    
    switch (application.applicationState) {
        case UIApplicationStateInactive:
            // The user has put the app in background, but not yet killed it.
            // She clicked or swiped the notification and the app now opens.
            
            KEYPushNotificationRecommendedHostAppAction *recommendedAction = [KEYSDK.sharedSDK recommendedHostAppActionWithNotification:remoteNotification];
    
            if (recommendedAction.letSDKHandleNotification) {
                // SDK recommends that we let it handle the notification (because it's a notification sent from keyper), so let's let it handle it:
                [KEYSDK.sharedSDK handleRemoteNotification:remoteNotification];
            }
            
            if (recommendedAction.showSDKRootNavigationController) {
                // SDK recommends that we show its view. So let's show it in the host app:
                [self.rootVC showLoggedInRootScreenAnimated:NO];
            }
            
            if (!recommendedAction.authenticateSDK) {
                // We don't need to authenticate SDK - reload host app's notifications view in that case (just an example!)
                [self.rootVC triggerNotificationsReload];
            }

            completionHandler(UIBackgroundFetchResultNewData);
            break;
        default:
            // App is either open or in backgrounding mode (i.e. the system wakes the app for a short time)
            // The user did not click or swipe the notification, so we don't switch views.
            // No need to handle this type of notifications in the SDK.
            break;
    }
}

```

As can be seen here, your app can decide to ignore the SDK's advice on what to do with a notification entirely, or just pass it in.

**Important Notes**: 

- Do not forget to configure the SDK before letting it validate and handle push notifications. Ideally, ```[KEYSDK.sharedSDK configure:]``` is called as the very first action in ```application:didFinishLaunchingWithOptions:```. 
- Also, most push notifications won't have any effect if the SDK is not authenticated. 
- Lastly, if ```application.applicationState``` is not ```UIApplicationStateInactive```, then we don't recommend to pass the notification on to the SDK.

### Customization

The SDK allows you to customize the look and feel of the SDK's logic and UI, in order to make them feel more native to your own app. The configuration of the SDK (that you saw earlier), offers a few more options. The following displays all available options and describes them one by one. In this example, we used a preprocessor macro (```BETA_BUILD```) to illustrate how beta builds can make use of the SDKs debugging features:

```
    
[KEYSDK.sharedSDK configure:^(KEYSDKConfiguration *c) {
#ifdef BETA_BUILD
    // Beta build
    c.enableSSLCertificatePinning = NO;
    c.enableAFNetworkingLogger = YES;
    c.showServerErrorsAsAlerts = YES;
    c.apiBaseURL = @"https://sandbox.api.keyper.io/api"
#else
    // Production build
    c.enableSSLCertificatePinning = YES;
    c.enableAFNetworkingLogger = NO;
    c.showServerErrorsAsAlerts = NO;
    c.apiBaseURL = @"https://api.keyper.io/api"
#endif
    c.tintColor = [UIColor colorWithRed:0 green:0.8 blue:0.6 alpha:1.0];
    c.navigationBarTintColor = [UIColor colorWithRed:0 green:0.8 blue:0.6 alpha:1.0];
    c.navigationBarTextColor = [UIColor whiteColor];
    c.navigationBarFont = [UIFont fontWithName:@"HelveticaNeue-Medium" size:17.f];
    c.sendTicketsBadgeImage = [UIImage imageNamed:@"badge_friend"];
    c.appSecret = @"sdk_ios_sample_secret";
}];

```

You can call ```configure:``` multiple times (e.g. to change ```apiBaseURL```), but some properties, e.g. colors and font will require reconstruction of the view hierarchy (```resetViews```) to have an effect.


| method | description | default value|
|--------|-------------|--------------|
| apiBaseURL | Allows you to change the base url of the keyper service. For example, if, you want to develop against the keyper sandbox environment. This really should be set by your app before using the SDK, but the SDK will also work if you call or re-call ```configure:``` to set or change ```apiBaseURL``` later on. Mind that all API requests performed before setting apiBaseURL will have failed. <br><br>Valid base URLs currently are: ```https://sandbox.api.keyper.io/api```<br> ```https://api.keyper.io/api``` | ```https://api.keyper.io/api``` |
| enableSSLCertificatePinning | If ```YES```, pins the expected SSL certificate of communication with ```apiBaseURL``` to *.keyper.io. Since keyper's development and sandbox environments have self-signed certificates, you should only set to ```YES``` when using production server (```https://api.keyper.io/api```).  | ```YES``` |
| tintColor | Takes a ```UIColor``` that is used throughout the app to highlight actions and accented text. | The default value resolves to #00cc99 (```[UIColor colorWithRed:0 green:0.8 blue:0.6 alpha:1.0]```) |
| navigationBarTintColor | Takes a ```UIColor``` for the very first screen's navigation bar background color. | The default value resolves to: #00c888 (```[UIColor colorWithRed:0 green:0.784 blue:0.533 alpha:1.0]```) |
| navigationBarTextColor | Takes a ```UIColor``` for the very first screen's navigation bar text and icon color. | The default value resolves to: #ffffff (```[UIColor whiteColor]```) |
| navigationBarFont | Takes a ```UIFont``` for all navigationbar title texts (size is adapted by the SDK though). If ```nil``` is given, system default is used. | ```nil``` |
| sendTicketsBadgeImage | Takes a ```UIImage``` that is used as badge in the send-tickets-view for users that are platform-friends with the current users. | ```keyper-ios-sdk-assets.bundle/badge_fav@2x/3x.png``` |
| bottomInset | Bottom inset of SDK views, e.g. if SDK is shown with a tab bar (since we cannot rely on autolayout here). | ```0.f``` |

### Events sent by the SDK

keyper SDK sends notifications via ```NSNotificationCenter``` to give the host app the chance to react to them. Their names are easily accessible in the public header ```KEYSDKConstants.h```. The following notifications are currently sent:

| Notification Name | Purpose | userInfo parameters |
|-------------------|---------|---------------------|
| KEYSDKDidLogoutNotificationName | The SDK will send this notification when a logout has completed (not only the host app can trigger a logout, but also certain errors returned by keyper's server, like invalid token errors). | none |
| KEYHostAppShouldChangeTabBarVisibilityNotificationName | If the host app shows the SDK with a tab bar, then the SDK can request to hide/show the tab bar with this notification. The reason for this is that some views (e.g. sending a ticket) require full screen presentation and have a button at the bottom that must not be overlapped.  | KEYHostAppShouldChangeTabBarVisibleKeyName: @(YES)/@(NO)  |
| KEYHostAppShouldChangeStatusBarStyleNotificationName | The SDK's views sometimes switch from light to dark status bar styles, and vice versa. If you need to implement this behavior, you can, by listening to this notification. | KEYHostAppShouldChangeStatusBarStyleObjectKeyName: @(UIStatusBarStyle) |
| KEYHostAppShouldShowKeyperSDKScreen | The SDK asks the host app to show the SDK's main view (rootNavigationController) as soon as possible - ideally, synchronously. E.g. if you integrated the SDK in a UITabBarController, show the SDK's tab now; or if you integrated it in a slide-out menu, show the SDK in the center view now.<br>This is mainly fired when the SDK has received a branch.io deep link (see above for reference), and the tickets overview should be shown. The SDK in turn will in most cases also pop to the tickets overview, and in some cases display a confirmation alert. | none |


### Events received by the SDK

keyper SDK listens to the following notifications by the host app to react to app lifecycle events. Their names are also accessible in the public header ```KEYSDKConstants.h```.

| Notification Name | Purpose |
|-------------------|---------|
| KEYApplicationDidBecomeActiveNotification | In order to keep the user's friend list up-to-date when sending a ticket, the view can be refreshed after the app has become active again. This is not vital to the SDK's functioning. You can implement it by sending an empty notification with name ```KEYApplicationDidBecomeActiveNotification``` whenever app delegate's ```applicationDidBecomeActive:``` is called.  |


### Sidenotes

The SDK stores cached API responses in the folder ```NSCachesDirectory/__keyper_sdk/``` folder, and non-volatile data (tickets, offers) in the folder ```NSDocumentDirectory/__keyper_sdk/```. All files are encrypted with AES256, and any user identifiers that are used as directory names are hashed with MD5. 

## Feedback
If you have any questions, feedback, bugs to report, please do not hesitate contacting dev@keyper.io
