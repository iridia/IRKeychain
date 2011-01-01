//
//  IRKeychainManager.m
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychainManager.h"


@implementation IRKeychainManager


+ (IRKeychainManager *) sharedManager {

	static dispatch_once_t predicate;
	static IRKeychainManager *sharedIRKeychainManager = nil;
	
	dispatch_once(&predicate, ^ {
		
		sharedIRKeychainManager = [[[self class] alloc] init];
	
	});
	
	return sharedIRKeychainManager;
	
}

- (id) init {
	
	self = [super init]; if (!self) return nil;
	
	self.errorDomain = IRIDIA_KEYCHAIN_DEFAULT_NSERROR_DOMAIN;
	
	return self;
	
}


- (NSArray *) keychainItemsOfKind:(IRKeychainItemKind)kind matchingPredicate:(NSDictionary *)predicateOrNil inAccessGroup:(NSString *)accessGroupOrNil {

	if (kind == IRKeychainItemKindAny) {
	
		NSMutableArray *results = [NSMutableArray array];
		
		NSArray* (^query)(IRKeychainItemKind) = ^ (IRKeychainItemKind queryKind) {
		
			return [self keychainItemsOfKind:queryKind matchingPredicate:predicateOrNil inAccessGroup:accessGroupOrNil];
		
		};
		
		[results addObjectsFromArray:query(IRKeychainItemKindPassword)];
		[results addObjectsFromArray:query(IRKeychainItemKindInternetPassword)];
		[results addObjectsFromArray:query(IRKeychainItemKindCertificate)];
		[results addObjectsFromArray:query(IRKeychainItemKindKey)];
		[results addObjectsFromArray:query(IRKeychainItemKindIdentity)];
		
		return results;
	
	}
	
	NSMutableDictionary *queryDictionary = [NSMutableDictionary dictionaryWithObjectsAndKeys:

		(id)SecClassFromIRKeychainItemKind(kind), (id)kSecClass,
		(id)kCFBooleanTrue, (id)kSecReturnData,
		(id)kCFBooleanTrue, (id)kSecReturnAttributes,
		(id)kCFBooleanTrue, (id)kSecReturnRef,
		(id)kCFBooleanTrue, (id)kSecReturnPersistentRef,
		(id)kSecMatchLimitAll, (id)kSecMatchLimit,
	
	nil];
	
	NSMutableArray *resultsArray = [NSMutableArray array];	
	
	
	if (predicateOrNil)
	for (id aKey in predicateOrNil)
	[queryDictionary setObject:[predicateOrNil objectForKey:aKey] forKey:aKey];
	
	
	OSStatus keychainQueryResults = errSecSuccess;
	keychainQueryResults = SecItemCopyMatching((CFDictionaryRef)queryDictionary, (CFTypeRef *)&resultsArray);
		
	if (keychainQueryResults != errSecSuccess) {
	
		if (keychainQueryResults != errSecItemNotFound)
		NSLog(@"Error: %@", irNSStringFromOSStatus(keychainQueryResults));
		
		return [NSArray array];
	
	}
			
	NSMutableArray *returnedItems = [NSMutableArray array];
	
	for (NSDictionary *securityItemRep in resultsArray) {
	
		Class keychainItemClass = IRKeychainItemClassFromKind(IRKeychainItemKindFromSecClass([securityItemRep objectForKey:kSecClass]));
		
		if (keychainItemClass == NULL)
		continue;

		[returnedItems addObject:[[((IRKeychainAbstractItem *)[keychainItemClass alloc]) initWithContentsOfSecurityItemDictionary:securityItemRep] autorelease]];
		
	}
	
	return returnedItems;
	
}

@end




