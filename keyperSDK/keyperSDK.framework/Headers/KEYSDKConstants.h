extern NSString * const KEYApplicationDidBecomeActiveNotification; // send this notification to notify keyper SDK of this event (e.g. for reloading data)

extern NSString * const KEYSDKDidLogoutNotificationName;

extern NSString * const KEYHostAppShouldChangeTabBarVisibilityNotificationName;
extern NSString * const KEYHostAppShouldChangeTabBarVisibleKeyName;

extern NSString * const KEYHostAppShouldChangeStatusBarStyleNotificationName;
extern NSString * const KEYHostAppShouldChangeStatusBarStyleObjectKeyName; // e.g. UIStatusBarStyleLightContent

extern NSString * const KEYPushNotificationKeyNotificationType;
extern NSString * const KEYPushNotificationKeyID;

extern NSString * const KEYHostAppShouldShowKeyperSDKScreen;

// These notifications are currently not sent in public SDK builds.
extern NSString * const KEYSDKProfileViewConfiguredNewAccountSuccessfullyNotificationName;
extern NSString * const KEYHostAppShouldShowSettingsScreenNotificationName;
extern NSString * const KEYHostAppShouldShowSettingsScreenNavigationControllerKeyName;
extern NSString * const KEYPopToTicketsRootViewControllerNotificationName;

typedef NS_ENUM(NSInteger, KEYMyTicketsPushNotificationsStatus) {
    KEYMyTicketsPushNotificationsStatusError = 0,
    KEYMyTicketsPushNotificationsStatusNotAuthenticated = 1,
    KEYMyTicketsPushNotificationsStatusEnabled = 2,
    KEYMyTicketsPushNotificationsStatusDisabled = 3,
    KEYMyTicketsPushNotificationsStatusUnknown = 4
};
