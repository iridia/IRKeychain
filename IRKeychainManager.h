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

- (NSArray *) keychainItemsOfKind:(IRKeychainItemKind)kind matchingPredicate:(NSDictionary *)predicateOrNil inAccessGroup:(NSString *)accessGroupOrNil;

//	Wrapper to the Security framework in Core Foundation.  Returns an array of keychain items that matches the identifier in the default order returned by CF.

//	- (NSArray *) passwordsMatchingLabel:predicate:inAccessGroup:
//	- (NSArray *) internetPasswordsMatchingServer:account:predicate:inAccessGroup:

@property (nonatomic, readwrite, retain) NSString *defaultAccessGroupName;

@end
