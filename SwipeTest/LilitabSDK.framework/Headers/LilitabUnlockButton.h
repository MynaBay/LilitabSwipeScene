//
//  LilitabUnlockButton.h
//  LilitabSDK
//
//  Created by Kevin Snow on 7/30/16.
//  Copyright © 2016 Lilitab. All rights reserved.
//

#import <UIKit/UIKit.h>

#define     LilitabSDK_UnlockAuthorizedNotification         @"LilitabUnlockButton_UnlockAuthorizedNotification"

@protocol LilitabUnlockButtonDelegate <NSObject>
-(void) showUnlockAuthorizationUI;
-(void) doUnlock;
@end

IB_DESIGNABLE

@interface LilitabUnlockButton : UIButton
@property (nonatomic, assign) IBInspectable BOOL requiresAuthorization;
@property (nonatomic,strong) IBInspectable id<LilitabUnlockButtonDelegate>  delegate;
@end
