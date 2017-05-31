//
//  KEYViewController.m
//  keyper-ios-sdk
//
//  Created by Manuel Maly on 06/24/2016.
//  Copyright (c) 2016 Manuel Maly. All rights reserved.
//

#import "KEYViewController.h"
#import "KEYSDK.h"
#import "KEYSDKConfiguration.h"

@interface KEYViewController ()

@end

@implementation KEYViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onStartButtonTapped:(id)sender {
    
    [KEYSDK.sharedSDK configure:^(KEYSDKConfiguration *c) {
        c.apiBaseURL = [NSURL URLWithString:@"https://develop.api.keyper.io/api/"];
        c.enableSSLCertificatePinning = NO;
        
        c.tintColor = [UIColor colorWithRed:1.f green:0.f blue:0.2f alpha:1.f];
        c.navigationBarTintColor = [UIColor colorWithRed: 0.937f green: 0.671f blue: 0.137f alpha: 1.f];
        c.navigationBarTextColor = [UIColor colorWithRed: 0.537f green: 0.0627f blue: 0.f alpha: 1.f];
        c.navigationBarFont = [UIFont fontWithName:@"Chalkduster" size:12.f];
        
        c.showServerErrorsAsAlerts = YES;
        c.enableAFNetworkingLogger = YES;
    }];
    
    [KEYSDK.sharedSDK authenticateWithRouteIdentifier:@"keyper" hostAppToken:@"INSERT TOKEN HERE" resultBlock:nil];
 
    UIViewController *vc = KEYSDK.sharedSDK.ticketsRootViewController;
    vc.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(onDoneTapped)];
    [self presentViewController:KEYSDK.sharedSDK.rootNavigationController animated:YES completion:nil];
}

- (void)onDoneTapped {
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
