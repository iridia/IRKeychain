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

@synthesize defaultAccessGroupName, errorDomain;


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
	
	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
		(id)kCFBooleanTrue, (id)kSecReturnData,
	#endif
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
	
	if (keychainQueryResults != errSecSuccess) {
	
		if (keychainQueryResults != errSecItemNotFound)
			NSLog(@"Error: %@", irNSStringFromOSStatus(keychainQueryResults));
		
		return [NSArray array];
	
	}
	
	[resultsArray retain];		//	Retains
	CFRelease(resultsArray);	//	Combats SecItemCopyMatching
	
	[resultsArray autorelease];
		
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

	IRKeychainAbstractItem *item = [self keychainItemMatchingPersistentReference:inPersistentReference];
	
	return item.secret;

}

- (id) keychainItemMatchingPersistentReference:(NSData *)inPersistentReference {
	
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
	
	__block IRKeychainAbstractItem *abstractItem = nil;
	
	[self forEachItemKind:^(IRKeychainItemKind kind) {
	
		if (abstractItem)
			return;
			
		CFTypeRef itemClass = SecClassFromIRKeychainItemKind(kind);
		
		NSDictionary *persistentRefQuery = [NSDictionary dictionaryWithObjectsAndKeys:
			(id)itemClass, (id)kSecClass,
			inPersistentReference, (id)kSecValuePersistentRef,
			(id)kCFBooleanTrue, (id)kSecReturnData,
			(id)kCFBooleanTrue, (id)kSecReturnAttributes,
			(id)kCFBooleanTrue, (id)kSecReturnRef,	//	This is so unintended
			(id)kCFBooleanTrue, (id)kSecReturnPersistentRef,
		nil];
		
		NSDictionary *queryResult = NULL;
		
		OSStatus results = SecItemCopyMatching((CFDictionaryRef)persistentRefQuery, (CFTypeRef *)&queryResult);
		if (results != errSecSuccess) {
			NSLog(@"Persistent ref can’t be converted: %@", irNSStringFromOSStatus(results));
			return;
		}
		
		abstractItem = [[(IRKeychainAbstractItem *)[IRKeychainItemClassFromKind(kind) alloc] initWithContentsOfSecurityItemDictionary:queryResult] autorelease];
		
	}];
	
	return abstractItem;

#else
	
	__block SecKeychainItemRef item = NULL;

	if (errSecSuccess != SecKeychainItemCopyFromPersistentReference((CFDataRef)inPersistentReference, (SecKeychainItemRef *)&item))
		return nil;
	
	if (!item)
		return nil;
	
	NSMutableArray *potentialItems = [NSMutableArray array];

	[self forEachItemKind:^(IRKeychainItemKind kind) {
		
		CFTypeRef itemClass = SecClassFromIRKeychainItemKind(kind);
		NSDictionary *dataQueryDictionary = [NSDictionary dictionaryWithObjectsAndKeys:
			(id)itemClass, (id)kSecClass,
			(CFArrayRef)[NSArray arrayWithObject:(id)item], (id)kSecMatchItemList,
			(id)kCFBooleanTrue, (id)kSecReturnAttributes,
			(id)kCFBooleanTrue, (id)kSecReturnData,
			(id)kSecMatchLimitOne, (id)kSecMatchLimit,
		nil];
		
		NSDictionary *fetchedData = nil;
		OSStatus keychainQueryResults = SecItemCopyMatching((CFDictionaryRef)dataQueryDictionary, (CFTypeRef *)&fetchedData);
		
		if (keychainQueryResults != errSecSuccess)
		if (keychainQueryResults != errSecItemNotFound)	//	We do expect search to sometimes fail 
			NSLog(@"Keychain Services: %@", irNSStringFromOSStatus(keychainQueryResults));
		
		if (fetchedData)
			[potentialItems addObject:[[(IRKeychainAbstractItem *)[IRKeychainItemClassFromKind(kind) alloc] initWithContentsOfSecurityItemDictionary:fetchedData] autorelease]];
		
	}];
	
	return [potentialItems lastObject];

#endif

}

@end




