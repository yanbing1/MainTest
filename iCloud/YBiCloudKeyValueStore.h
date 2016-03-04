//
//  iCloudKeyValueStore.h
//  MyICloudDemo
//
//  Created by 曹燕兵 on 16/3/2.
//  Copyright © 2016年 曹燕兵. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface iCloudKeyValueStore : NSUbiquitousKeyValueStore
/**
 *  单例
 *
 *  @return 单例对象
 */
+(id)sharedStore;
/**
 *  储存或者修改iCloud中key值对应的存储内容
 *
 *  @param info 存储内容
 *  @param key  存储标签
 *
 *  @return 存储结果，成功为YES,反之为NO
 */
-(BOOL)storeInformation:(id) info Key:(NSString*)key;
/**
 *  在iCloud中搜索key值对应的存储内容
 *
 *  @param key 存储标签
 *
 *  @return 存储内容
 */
-(id)seekinfomationWithKey:(NSString *)key;
/**
 *  删除iCloud中key值对应的存储内容
 *
 *  @param key 存储标签
 *
 *  @return 删除结果，成功返回YES,反之返回NO
 */
-(BOOL)deleteInformationWithKey:(NSString *)key;
@end
