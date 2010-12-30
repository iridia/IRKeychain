//
//  IRKeychainAbstractItem.h
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychainDefines.h"
//	#import "IRKeychain.h"

@interface IRKeychainAbstractItem : NSObject

- (id) initWithIdentifier:(NSString *)identifier;

//	Makes a new object, which is not synced.


- (id) initWithCoreFoundationReference:(CFTypeRef)reference;

//	Makes a new object and fills its values using the reference.  Subclasses should override this method and be stricter in acceptance.


- (BOOL) synchronizeWithError:(NSError **)error overwrittingOriginal:(BOOL)shouldOverwrite;

//	Synchronize the item with the keychain services.  Returns a BOOL that indicates success or failure.
//	If shouldOverwrite is YES, overwrites the original.


- (BOOL) synchronize;

//	return [self synchronizeWithErorr:nil overwrittingOriginal:YES]


- (BOOL) removeWithError:(NSError **)error;

//	Removes the item from the keychain.  Returns a BOOL that indicates success or failure.


- (BOOL) remove;

//	return [self removeWithError:nil];


@property (nonatomic, readwrite, assign) IRKeychainItemAccessCondition accessCondition;
@property (nonatomic, readwrite, assign) NSString *accessGroup;

@property (nonatomic, readonly, retain) NSString *identifier;

@end
