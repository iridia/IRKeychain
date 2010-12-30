//
//  IRKeychain.h
//  IRKeychain
//
//  Created by Evadne Wu on 12/29/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>
#import <Security/Security.h>










#pragma mark Defines

#ifndef __IRKeychain__
#define __IRKeychain__


typedef enum {
	
	IRKeychainItemKindAny,
	IRKeychainItemKindPassword,		//	kSecClassGenericPassword
	IRKeychainItemKindInternetPassword,	//	kSecClassInternetPassword
	IRKeychainItemKindCertificate,		//	kSecClassCertificate
	IRKeychainItemKindKey,			//	kSecClassKey
	IRKeychainItemKindIdentity		//	kSecClassIdentity

} IRKeychainItemKind;


typedef enum {
	
	IRKeychainItemAccessibleWhenUnlocked,
	IRKeychainItemAccessibleAfterFirstUnlock,
	IRKeychainItemAccessibleAlways,
	IRKeychainItemAccessibleWhenUnlockedThisDeviceOnly,
	IRKeychainItemAccessibleAfterFirstUnlockThisDeviceOnly,
	IRKeychainItemAccessibleAlwaysThisDeviceOnly
	
} IRKeychainItemAccessCondition;

//	Conveniences for debugging, internal use, etc.

extern NSString* NSStringFromIRKeychainItemKind (IRKeychainItemKind kind);
extern CFTypeRef SecClassFromIRKeychainItemKind(IRKeychainItemKind kind);

extern NSString* irNSStringFromOSStatus(OSStatus status);

#endif










#pragma mark -
#pragma mark Main Class





@interface IRKeychain : NSObject

+ (IRKeychain *) sharedKeychain;

- (NSArray *) itemsOfKind:(IRKeychainItemKind)kind matchingPredicate:(NSDictionary *)predicateOrNil inAccessGroup:(NSString *)accessGroupOrNil;

//	Wrapper to the Security framework in Core Foundation.  Returns an array of keychain items that matches the identifier in the default order returned by CF.

//	- (NSArray *) passwordsMatchingLabel:predicate:inAccessGroup:
//	- (NSArray *) internetPasswordsMatchingServer:account:predicate:inAccessGroup:

@property (nonatomic, readwrite, retain) NSString *defaultAccessGroupName;

@end










# pragma mark -
# pragma mark Keychain Items





@interface IRKeychainAbstractItem : NSObject

- (id) initWithIdnetifier:(NSString *)identifier;

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





@interface IRKeychainPasswordItem : IRKeychainAbstractItem

@property (nonatomic, readonly, retain) NSDate *creationDate;
@property (nonatomic, readonly, retain) NSDate *lastModificationDate;

//	Note that before an item is synced to the keychain, these dates could be nil.


@property (nonatomic, readwrite, retain) NSNumber *creatorCodeRepresentation;

@property (nonatomic, readwrite, assign, getter=isInvisible) BOOL invisible;
@property (nonatomic, readwrite, assign, getter=isNegative) BOOL negative;

@property (nonatomic, readwrite, retain) NSString *associatedAccountName;
@property (nonatomic, readwrite, retain) NSString *associatedServiceName;

@property (nonatomic, readwrite, retain) NSString *userDescription;
@property (nonatomic, readwrite, retain) NSString *userComment;

@property (nonatomic, readwrite, retain) NSString *userLabel;
@property (nonatomic, readwrite, retain) NSData *userGenericData;

@end





//	FIXME: THESE ITEMS ARE NOT YET IMPLEMENTED
	
@interface IRKeychainInternetPasswordItem : IRKeychainAbstractItem

@end

	   
@interface IRKeychainCertificateItem : IRKeychainAbstractItem

@end


@interface IRKeychainKeyItem : IRKeychainAbstractItem

@end


@interface IRKeychainIdentityItem : IRKeychainAbstractItem

@end




