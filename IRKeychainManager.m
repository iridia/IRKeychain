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
		(id)kCFBooleanTrue, (id)kSecReturnAttributes,
		(id)kCFBooleanTrue, (id)kSecReturnRef,
		(id)kSecMatchLimitAll, (id)kSecMatchLimit,
	
	nil];
	
	NSMutableDictionary *resultsDictionary = [NSMutableDictionary dictionary];	
	
	
	if (predicateOrNil)
	for (id aKey in predicateOrNil)
	[queryDictionary setObject:[predicateOrNil objectForKey:aKey] forKey:aKey];
	
	
//	The identifier is an umbrella term for different keys, for different keychain item classes.
//	FIXME: Add identifier support for other kinds of items
	

	OSStatus keychainServicesResults = errSecSuccess;
	keychainServicesResults = SecItemCopyMatching((CFDictionaryRef)queryDictionary, (CFTypeRef *)&resultsDictionary);
	
	if (keychainServicesResults != errSecSuccess) {
	
		NSLog(@"Error: %@", irNSStringFromOSStatus(keychainServicesResults));
		return [NSArray array];
	
	}
	
	NSLog(@"\n\n queryDictionary %@, resultsDictionary %@", queryDictionary, resultsDictionary);
	
	return [NSArray array];	
	
}

- (id) itemOfKind:(IRKeychainItemKind)kind withIdentifier:(NSString *)identifier {

	return [[self keychainItemsOfKind:kind matchingPredicate:nil inAccessGroup:nil] objectAtIndex:0];
	
}

- (id) createdItemOfKind:(IRKeychainItemKind)kind withIdentifier:(NSString *)identifier {
	
	return [[[IRKeychainItemClassFromKind(kind) alloc] initWithIdentifier:identifier] autorelease];
	
}


@end




