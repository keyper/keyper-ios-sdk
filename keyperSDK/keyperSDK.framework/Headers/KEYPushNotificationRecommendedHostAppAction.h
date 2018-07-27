//
//  KEYPushNotificationRecommendedHostAppAction.h
//  Pods
//
//  Created by Manuel Maly on 10.06.16.
//
//

#import <Foundation/Foundation.h>

@interface KEYPushNotificationRecommendedHostAppAction : NSObject

@property (assign, nonatomic, readonly) BOOL authenticateSDK;
@property (assign, nonatomic, readonly) BOOL letSDKHandleNotification;
@property (assign, nonatomic, readonly) BOOL showSDKRootNavigationController;

+ (KEYPushNotificationRecommendedHostAppAction *)actionWithAuthenticateAtSDK:(BOOL)authenticateSDK letSDKHandleNotification:(BOOL)letSDKHandleNotification showSDKRootNavigationController:(BOOL)showSDKRootNavigationController;

@end
