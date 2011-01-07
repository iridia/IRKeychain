//
//  IRKeychainManager.h
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychain.h"


@interface IRKeychainManager : NSObject

+ (IRKeychainManager *) sharedManager;

- (NSString *) secretFromPersistentReference:(NSData *)inPersistentReference;

//	Useful when you have a persistent reference ref data but do not want things other than the secret


- (id) keychainItemMatchingPersistentReference:(NSData *)inPersistentReference ofKind:(IRKeychainItemKind)inKind;

- (NSArray *) keychainItemsOfKind:(IRKeychainItemKind)kind matchingPredicate:(NSDictionary *)predicateOrNil inAccessGroup:(NSString *)accessGroupOrNil;

//	Returns an array of items matching a certain predicate that is the same thing you can pass to SecItemCopyMatching().  Item order not guaranteed.


@property (nonatomic, readwrite, retain) NSString *defaultAccessGroupName;

//	This access group name matches the name you specify in your app entitlements, to share keychain items across a suite of apps.


@property (nonatomic, readwrite, retain) NSString *errorDomain;

//	Default is IRIDIA_KEYCHAIN_DEFAULT_NSERROR_DOMAIN


//	FIXME: add more defaults, over configuration

@end
