//
//  IRKeychainInternetPasswordItem.m
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychainInternetPasswordItem.h"


@implementation IRKeychainInternetPasswordItem

- (NSDictionary *) securityItemQueryDictionary {

	NSMutableDictionary *returnedDictionary = [[super securityItemQueryDictionary] mutableCopy];
	
	if (self.associatedAccountName)
	[returnedDictionary setObject:self.associatedAccountName forKey:(id)kSecAttrAccount];
	
	return returnedDictionary;

}

- (NSDictionary *) securityItemAttributesDictionary {

	NSMutableDictionary *returnedDictionary = [[super securityItemAttributesDictionary] mutableCopy];
	
	if (self.associatedAccountName)
	[returnedDictionary setObject:self.associatedAccountName forKey:(id)kSecAttrAccount];
	
	return returnedDictionary;

}

@end
