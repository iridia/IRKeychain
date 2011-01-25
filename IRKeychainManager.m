//
//  IRKeychainManager.m
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychainManager.h"


@interface IRKeychainManager ()

- (void) forEachItemKind:(void(^)(IRKeychainItemKind kind))callback;

@end


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





- (void) forEachItemKind:(void(^)(IRKeychainItemKind kind))callback {

	callback(IRKeychainItemKindPassword);
	callback(IRKeychainItemKindInternetPassword);
	callback(IRKeychainItemKindCertificate);
	callback(IRKeychainItemKindKey);
	callback(IRKeychainItemKindIdentity);

}





- (NSArray *) keychainItemsOfKind:(IRKeychainItemKind)kind matchingPredicate:(NSDictionary *)predicateOrNil inAccessGroup:(NSString *)accessGroupOrNil {

	if (kind == IRKeychainItemKindAny) {
	
		NSMutableArray *results = [NSMutableArray array];
		
		[self forEachItemKind: ^ (IRKeychainItemKind queryKind) {
		
			NSLog(@"forEachItemKind called for kind %d", queryKind);
		
			[results addObjectsFromArray:[self keychainItemsOfKind:queryKind matchingPredicate:predicateOrNil inAccessGroup:accessGroupOrNil]];
		
		}];
		
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
	
	NSArray *resultsArray = nil;	
	
	
	if (predicateOrNil)
	for (id aKey in predicateOrNil)
	[queryDictionary setObject:[predicateOrNil objectForKey:aKey] forKey:aKey];
	
	
	OSStatus keychainQueryResults = errSecSuccess;
	keychainQueryResults = SecItemCopyMatching((CFDictionaryRef)queryDictionary, (CFTypeRef *)&resultsArray);
	
	[resultsArray retain];		//	Retains
	CFRelease(resultsArray);	//	Combats SecItemCopyMatching
	
	[resultsArray autorelease];
		
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

- (id) secretFromPersistentReference:(NSData *)inPersistentReference {

	NSMutableArray *possibleItems = [NSMutableArray array];

	[self forEachItemKind: ^ (IRKeychainItemKind kind) {
	
		id returnedItem = [self keychainItemMatchingPersistentReference:inPersistentReference ofKind:kind];
		
		if (!returnedItem)
		return;
		
		[possibleItems addObject:returnedItem];
	
	}];
	
	if ([possibleItems count] == 0) return nil;
	
	return ((IRKeychainAbstractItem *)[possibleItems objectAtIndex:0]).secret;

}

- (id) keychainItemMatchingPersistentReference:(NSData *)inPersistentReference ofKind:(IRKeychainItemKind)inKind {

	NSAssert((inKind != IRKeychainItemKindAny), @"-keychainItemMatchingPersistentReference:ofKind: should not be passed IRKeychainItemKindAny.");

	NSDictionary *resultsDictionary = nil;
	OSStatus keychainQueryResults = SecItemCopyMatching((CFDictionaryRef)[NSDictionary dictionaryWithObjectsAndKeys:
	
		inPersistentReference, (id)kSecValuePersistentRef,
		(id)kCFBooleanTrue, (id)kSecReturnData,
		(id)kCFBooleanTrue, (id)kSecReturnAttributes,
		(id)kCFBooleanTrue, (id)kSecReturnRef,
		(id)kCFBooleanTrue, (id)kSecReturnPersistentRef,
		(id)kSecMatchLimitOne, (id)kSecMatchLimit,
		
	nil], (CFTypeRef *)&resultsDictionary);
	
	[resultsDictionary retain];	//	Retains
	CFRelease(resultsDictionary);	//	Combats SecItemCopyMatching
	
	[resultsDictionary autorelease];

	
	if (keychainQueryResults != errSecSuccess) {
	
		NSLog(@"Keychain Services: %@", irNSStringFromOSStatus(keychainQueryResults));
		return nil;
	
	}
	
	return [[(IRKeychainAbstractItem *)[IRKeychainItemClassFromKind(inKind) alloc] initWithContentsOfSecurityItemDictionary:resultsDictionary] autorelease];

}

@end




