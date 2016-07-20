//
//  LilitabAccessory.h
//  LilitabSDK
//
//  Created by Kevin Snow on 6/28/14.
//  Copyright (c) 2014 Lilitab. All rights reserved.
//

#import <Foundation/Foundation.h>

    // Accessory Types
typedef NS_ENUM(NSInteger, Lilitab_Accessory_Type)
{
    LILITAB_NO_ACCESSORY,
    LILITAB_SWIPE,
    LILITAB_DOCK
};

    // LED states
typedef NS_ENUM(NSInteger, LilitabSDK_LED_Mode)
{
    LED_Off,
    LED_On,
    LED_Blink1,
    LED_Blink2,
    LED_Blink3,
    LED_Blink4,
    LED_SwipeForward,
    LED_SwipeReverse
};

    // Names used with NSNotificationCenter to be notified of dock status events
#define     LilitabSDK_DockStatusNotification           @"LilitabSDK-DockStatusNotification"

    // Names used with NSNotificationCenter to be notified of connect/disconnect events
#define     LilitabSDK_DidConnectNotification           @"Liliswipe_DidConnectNotification"
#define     LilitabSDK_DidDisconnectNotification        @"Liliswipe_DidDisconnectNotification"
    // Deprecated. Use LilitabSDK_ versions
#define     Liliswipe_DidConnectNotification            @"Liliswipe_DidConnectNotification"
#define     Liliswipe_DidDisconnectNotification         @"Liliswipe_DidDisconnectNotification"


@interface LilitabSDK : NSObject

    /////////////////////////////////////////////////////////////////////
    // singleton - Singleton object for communication with lilitab accessories
    //
+(LilitabSDK*) singleton;


    /////////////////////////////////////////////////////////////////////
    // accessoryType - Type of Lilitab accessory attached.
    //
@property (nonatomic,readonly) Lilitab_Accessory_Type accessoryType;


    /////////////////////////////////////////////////////////////////////
    // isAttached - readonly property containing presence of liliswipe
    //
@property (nonatomic,readonly)  BOOL isAttached;


    /////////////////////////////////////////////////////////////////////
    // status - The completionBLock is executed after the status information
    // has been read from the swipe.
    //
-(void) status:(void (^)(BOOL success,NSDictionary* results))completionBlock;


    /////////////////////////////////////////////////////////////////////
    // ledState - Controls the LEDs on the swipe. Defaults to LED_Off.
    //
@property (nonatomic,assign)    LilitabSDK_LED_Mode  ledState;


    /////////////////////////////////////////////////////////////////////
    // setHeadTimeTo - Time passed to the card reader head.
    //
-(void) setHeadTimeTo:(NSDate*)date;


    /////////////////////////////////////////////////////////////////////
    // noPowerBlinkDuration - Controls the duration between blinks in
    // milliseconds if not power is present. Defaults to 0 (no blink)
    //
@property (nonatomic,assign)    NSTimeInterval      noPowerBlinkDuration;


    /////////////////////////////////////////////////////////////////////
    // Swiping - Set the swipeBlock property to code to execute for a swipe
    // Use the enable property to enable/disable swipeBlock execution.
    // After enabling swipe, it stays active until a swipe, timeout or error.
    // A timeout of 0 is infinite
    //
@property (nonatomic,copy)                    void(^swipeBlock)(NSDictionary* swipeData);
@property (nonatomic,assign)    BOOL                enableSwipe;            // default: NO
@property (nonatomic,assign)    BOOL                allowMultipleSwipes;    // default: NO
@property (nonatomic,assign)    NSTimeInterval      swipeTimeout;


    /////////////////////////////////////////////////////////////////////
    // Speaker override lets app force sound out speakers with headphone
    // jack plugged in.
    //
@property (nonatomic,assign)    BOOL                enableSpeakerOverride;


    /////////////////////////////////////////////////////////////////////
    // Lock & Unlock a Dock accessory
    //
-(void) lockWithCompletion:(void (^)(BOOL success))completionBlock;
-(void) unlockWithCompletion:(void (^)(BOOL success))completionBlock;


    /////////////////////////////////////////////////////////////////////
    // Dock status events
    //
@property (nonatomic,assign)    NSTimeInterval      dockLiveStatusInterval;


    /////////////////////////////////////////////////////////////////////
    // Firmware Updating
    //
-(void) updateFirmware:(NSData*)firmware
               options:(NSDictionary*)optionsDict
          withProgress:(void (^)(float percent0to1))progressBlock
        withCompletion:(void (^)(BOOL success))completionBlock;

-(void) cancelFirmwareUpdate;


    /////////////////////////////////////////////////////////////////////
    // enableAttachmentNotification - After adding NSNotification observers to
    // LilitabSDK_DidConnectNotification & LilitabSDK_DidDisconnectNotification this is
    // called to generate notifications.
    //
@property (nonatomic,assign)    BOOL  enableAttachmentNotification;


    /////////////////////////////////////////////////////////////////////
    // version - return a version string of the library
    //
@property (nonatomic,readonly)  NSString*  version;


    /////////////////////////////////////////////////////////////////////
    // debugMessages - Have library pass debug strings to app.
    //
    // Used for SDK development/testing
    //
@property (nonatomic,copy)      void(^debugMessages)(NSString* msg);

    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////
    // Sending a raw command string
    //
-(void) sendCommand:(NSString*)cmd withCompletion:(void (^)(BOOL success,NSDictionary* results))completionBlock;

-(void) testFlashWithCompletion:(void (^)(BOOL success,NSDictionary* results))completionBlock;


    //////////////////////////////////////////////////////////
    // deprecated methods
@property (nonatomic,copy)      void(^dockStatus)(NSDictionary<NSString*,NSString*>* dictionary);
@property (nonatomic,copy)      void(^dockLiveStatus)(NSMutableDictionary* dictionary);
@property (nonatomic,copy)      void(^dockCachedStatus)(NSMutableDictionary* dictionary);
@property (nonatomic,copy)      void(^dockMessages)(NSString* message);
-(void) unlockForUser:(NSString*)userName password:(NSString*)password completion:(void (^)(BOOL success))completionBlock;
    ///////////////////////////////////////////////////////////



    /////////////////////////////////////////////////////////////////////

@end


    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////

@interface Liliswipe : LilitabSDK   // Deprecated. Use LilitabSDK singleton

+(Liliswipe*) sharedSwipe;

@end

    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////

