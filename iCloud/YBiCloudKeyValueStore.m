//
//  iCloudKeyValueStore.m
//  MyICloudDemo
//
//  Created by 曹燕兵 on 16/3/2.
//  Copyright © 2016年 曹燕兵. All rights reserved.
//

#import "YBiCloudKeyValueStore.h"

@implementation iCloudKeyValueStore

+(id)sharedStore{
    static iCloudKeyValueStore *store =nil;
    dispatch_once_t oncetoken;
    dispatch_once(&oncetoken, ^{
        store = [[iCloudKeyValueStore alloc]init];
    });
    return store;
}

-(BOOL)storeInformation:(id)info Key:(NSString *)key{
    [self setObject:info forKey:key];
   return [self synchronize];
}

-(id)seekinfomationWithKey:(NSString *)key{
    return [self objectForKey:key];
}

-(BOOL)deleteInformationWithKey:(NSString *)key{
    [self removeObjectForKey:key];
    return [self synchronize];
}
@end
