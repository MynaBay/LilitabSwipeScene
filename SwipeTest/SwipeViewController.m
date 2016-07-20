//
//  SwipeViewController.m
//  SwipeTest
//
//  Created by Kevin Snow on 7/19/16.
//  Copyright © 2016 MynaBay Inc. All rights reserved.
//

#import "SwipeViewController.h"
#import <LilitabSDK/LilitabSDK.h>

@interface SwipeViewController ()

@property (nonatomic,weak) IBOutlet UILabel*    label;
@property (nonatomic,weak) IBOutlet UITextView* textView;

@end

@implementation SwipeViewController

-(void) viewWillAppear:(BOOL)animated
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(lilitabConnected:)    name:LilitabSDK_DidConnectNotification    object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(lilitabDisconnected:) name:LilitabSDK_DidDisconnectNotification object:nil];
    
    [LilitabSDK singleton].enableAttachmentNotification = YES;
}

-(void) viewWillDisappear:(BOOL)animated
{
    [LilitabSDK singleton].enableSwipe = NO;
    [LilitabSDK singleton].swipeBlock = nil;
    [LilitabSDK singleton].ledState = LED_Off;
    [LilitabSDK singleton].enableAttachmentNotification = NO;
    
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

-(void) lilitabConnected:(NSNotification*)notification
{
    self.label.text = @"Lilitab Swipe Connected";
    
    [LilitabSDK singleton].ledState = LED_On;
    [LilitabSDK singleton].swipeBlock = ^(NSDictionary* swipeData)
                                                    {
                                                        [LilitabSDK singleton].ledState = LED_Off;
                                                        self.textView.text = [NSString stringWithFormat:@"%@",swipeData];
                                                    };
    [LilitabSDK singleton].enableSwipe = YES;
}

-(void) lilitabDisconnected:(NSNotification*)notification
{
    self.label.text = @"Lilitab Swipe Disconnected";
    
    [LilitabSDK singleton].enableSwipe = NO;
    [LilitabSDK singleton].swipeBlock = nil;
    [LilitabSDK singleton].ledState = LED_Off;
    
    self.textView.text = @"";
}

@end
