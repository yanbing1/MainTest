//
//  iCloud.h
//  iCloud Document Sync
//
//  Created by iRare Media. Last updated January 2014.
//  Available on GitHub. Licensed under MIT with Attribution.
//

// Check for Objective-C Modules
#if __has_feature(objc_modules)
    // We recommend enabling Objective-C Modules in your project Build Settings for numerous benefits over regular #imports. Read more from the Modules documentation: http://clang.llvm.org/docs/Modules.html
    @import Foundation;
    @import UIKit;
#else
    #import <Foundation/Foundation.h>
    #import <UIKit/UIKit.h>
#endif

// Import iCloudDocument
//#import <iCloud/iCloudDocument.h>
#import "YBiCloudDocument.h"

// Check for ARC
#if !__has_feature(objc_arc)
    // Add the -fobjc-arc flag to enable ARC for only these files, as described in the ARC documentation: http://clang.llvm.org/docs/AutomaticReferenceCounting.html
    #error iCloudDocumentSync is built with Objective-C ARC. You must enable ARC for iCloudDocumentSync.
#endif

// Ensure that the build is for iOS 5.1 or higher
#ifndef __IPHONE_5_1
    #error iCloudDocumentSync is built with features only available is iOS SDK 5.1 and later.
#endif

// Create a constant for accessing the documents directory
#define DOCUMENT_DIRECTORY @"Documents"
@class YBiCloud;
@protocol YBiCloudDelegate;
NS_CLASS_AVAILABLE_IOS(5_1) @interface YBiCloud : NSObject




/** @name Singleton */

/** iCloud shared instance object
 @return The shared instance of iCloud */
+ (id)sharedCloud;

/** @name Delegate */

/** iCloud Delegate helps call methods when document processes begin or end */
@property (weak, nonatomic) id <YBiCloudDelegate> delegate;

/**
 *  查询
 */
@property (strong) NSMetadataQuery *query;

/**
 *  文件列表
 */
@property (strong) NSMutableArray *fileList;

/**
 *  之前查询结果
 */
@property (strong) NSMutableArray *previousQueryResults;

/**
 *  是否打印log信息
 */
@property BOOL verboseLogging;

/**
 *  是否打印log详细信息
 */
@property BOOL verboseAvailabilityLogging;

/**
 *  检查iCloud是否可用，基本每个方法都要调用，以确保iCloud是可用的
 *
 *  @return 可用返回YES
 */
- (BOOL)checkCloudAvailability;

/**
 *  检查container是否可用
 *
 *  @return 可用返回YES
 */
- (BOOL)checkCloudUbiquityContainer;

/**
 *  获取当前应用的根路径
 *
 *  @return 返回根路径url
 */
- (NSURL *)ubiquitousContainerURL;

/**
 *  获取当前应用的根目录的url
 *
 *  @return 返回根目录的url
 */
- (NSURL *)ubiquitousDocumentsDirectoryURL;

/**
 *  同步更新iCloud文件
 */
- (void)updateFiles;

/**
 *  检查document是否存在，存在的时候保存并关闭，不存在的时候闲创建然后关闭
 *
 *  @param documentName 文件后缀名称
 *  @param content      存储内容
 *  @param handler      document创建成功的回调
 */
- (void)saveAndCloseDocumentWithName:(NSString *)documentName withContent:(NSData *)content completion:(void (^)(UIDocument *cloudDocument, NSData *documentData, NSError *error))handler __attribute__((nonnull));

/**
 *  同步本地文件到云端
 *
 *  @param repeatingHandler 每个本地文件同步完成的回调，每当有一个文件同步完成就调用一次
 *  @param completion       所有本地文件同步完成的回调，只调用一次
 */
- (void)uploadLocalOfflineDocumentsWithRepeatingHandler:(void (^)(NSString *documentName, NSError *error))repeatingHandler completion:(void (^)(void))completion __attribute__((nonnull (1)));

/**
 *  同步一个本地文件到云端
 *
 *  @param documentName 存储在应用document文件夹下的文件后缀名，此处不能为空
 *  @param handler      文件同步完成后的回调
 */
- (void)uploadLocalDocumentToCloudWithName:(NSString *)documentName completion:(void (^)(NSError *error))handler __attribute__((nonnull));

/**
 *  分享一个文件到网络，以便他人访问
 *
 *  @param documentName 需要共享到网上的文件名称，此处不能为空
 *  @param handler      文件共享成功的回调
 *
 *  @return 他人访问共享文件时的URL
 */
- (NSURL *)shareDocumentWithName:(NSString *)documentName completion:(void (^)(NSURL *sharedURL, NSDate *expirationDate, NSError *error))handler __attribute__((nonnull));

/**
 *  删除存储在云端的文件
 *
 *  @param documentName 要删除的文件，此处不能为空
 *  @param handler      当文件成功从云端删除时候的回调
 */
- (void)deleteDocumentWithName:(NSString *)documentName completion:(void (^)(NSError *error))handler __attribute__((nonnull (1)));

/**
 *  将云端的文件移除到本地沙盒document路径
 *
 *  @param documentName 需要从云端移除到本地的文件名称
 *  @param handler      文件操作成功后的回调
 */
- (void)evictCloudDocumentWithName:(NSString *)documentName completion:(void (^)(NSError *error))handler __attribute__((nonnull));

/**
 *  当云端存在某文件时，打开该文件，当不存在时创建此名称文件
 *
 *  @param documentName 要打开的文件名称，此处不能为空
 *  @param handler      当文件打开或者创建成功的回调
 */
- (void)retrieveCloudDocumentWithName:(NSString *)documentName completion:(void (^)(UIDocument *cloudDocument, NSData *documentData, NSError *error))handler __attribute__((nonnull));

/**
 *  查找在云端存储的某个文件
 *
 *  @param documentName 文件名称
 *
 *  @return 文件，如果云端没有此文件、iCloud不可用或者查找出错均会返回nil
 */
- (YBiCloudDocument *)retrieveCloudDocumentObjectWithName:(NSString *)documentName __attribute__((nonnull));

/**
 *  查找某个文件是否在云端
 *
 *  @param documentName 文件名称
 *
 *  @return 查找结果
 */
- (BOOL)doesFileExistInCloud:(NSString *)documentName __attribute__((nonnull));
/**
 *  查找一个云端文件的大小
 *
 *  @param documentName 文件名称
 *
 *  @return 文件大小
 */
- (NSNumber *)fileSize:(NSString *)documentName __attribute__((nonnull));

/**
 *  记录一个iCloud文件最后修改日期
 *
 *  @param documentName 文件名称
 *
 *  @return 最后修改日期
 */
- (NSDate *)fileModifiedDate:(NSString *)documentName __attribute__((nonnull));

/**
 *  记录一个文件开始存储到云端的日期
 *
 *  @param documentName 文件名称
 *
 *  @return 开始存储到云端的日期
 */
- (NSDate *)fileCreatedDate:(NSString *)documentName __attribute__((nonnull));

/**
 *  得到存储到云端的所有文件列表
 *
 *  @return 存储到云端的所有文件
 */
- (NSArray *)getListOfCloudFiles;

/**
 *  重新命名一个云端文件
 *
 *  @param documentName 需要重新命名的文件
 *  @param newName      文件新名称
 *  @param handler      重新命名完成后的回调
 */
- (void)renameOriginalDocument:(NSString *)documentName withNewName:(NSString *)newName completion:(void (^)(NSError *error))handler __attribute__((nonnull));
/**
 *  在iCloud中复制一个文件
 *
 *  @param documentName 需要被复制的文件，当此文件不存在的时候会有error
 *  @param newName      复制后的文件名称
 *  @param handler      操作完成后的回调
 */
- (void)duplicateOriginalDocument:(NSString *)documentName withNewName:(NSString *)newName completion:(void (^)(NSError *error))handler __attribute__((nonnull));

/**
 *  得到iCloud中某个文件的状态（UIDocumentState）
 *
 *  @param documentName 文件名称
 *  @param handler      操作完成的回调
 */
- (void)documentStateForFile:(NSString *)documentName completion:(void (^)(UIDocumentState *documentState, NSString *userReadableDocumentState, NSError *error))handler __attribute__((nonnull));

/**
 *  监听iCloud中某个文件的状态改变
 *
 *  @param documentName 文件名称
 *  @param sender       监听者
 *  @param selector     触发事件名称
 *
 *  @return 监听成功返回YES，否则返回NO
 */
- (BOOL)monitorDocumentStateForFile:(NSString *)documentName onTarget:(id)sender withSelector:(SEL)selector __attribute__((nonnull));

/**
 *  停止监听iCloud中某个文件的状态改变
 *
 *  @param documentName 文件名称
 *  @param sender       监听者
 *
 *  @return 停止返回YES，否则返回NO
 */
- (BOOL)stopMonitoringDocumentStateChangesForFile:(NSString *)documentName onTarget:(id)sender __attribute__((nonnull));

/**
 *  在一个具体文件中寻找所有的冲突
 *
 *  @param documentName 文件名称
 *
 *  @return 所有冲突
 */
- (NSArray *)findUnresolvedConflictingVersionsOfFile:(NSString *)documentName __attribute__((nonnull));
/**
 *  解决一个文件的冲突
 *
 *  @param documentName    文件名称
 *  @param documentVersion 最终保留下来的文件版本
 */
- (void)resolveConflictForFile:(NSString *)documentName withSelectedFileVersion:(NSFileVersion *)documentVersion __attribute__((nonnull));


/**
 *  保存并关闭iCloud文件
 *
 *  @param documentName 文件名称
 *  @param content      文件内容
 *  @param __deprecated 操作完成的回调
 */
- (void)saveChangesToDocumentWithName:(NSString *)documentName withContent:(NSData *)content completion:(void (^)(UIDocument *cloudDocument, NSData *documentData, NSError *error))handler __attribute__((nonnull)) __deprecated;

/** DEPRECATED. Use uploadLocalOfflineDocuments instead, like so: [[iCloud sharedCloud] uploadLocalOfflineDocuments];
 
 @deprecated Deprecated in version 7.0. Use uploadLocalOfflineDocuments instead.
 @param delegate The iCloudDelegate object to be used for delegate notifications */
/**
 *  ios 7.0之后用uploadLocalOfflineDocuments方法代替
 *
 *  @param delegate 代理
 */
+ (void)uploadLocalOfflineDocumentsWithDelegate:(id<YBiCloudDelegate>)delegate __deprecated;

/** DEPRECATED. Use updateFiles instead, like so: [[iCloud sharedCloud] updateFiles];
 
 @deprecated Deprecated in version 7.0. Use updateFiles instead.
 @param delegate The iCloudDelegate object to be used for delegate notifications */
/**
 *  iOS 7.0之后使用，之前用updateFiles方法代替此方法
 *
 *  @param delegate 代理
 */
+ (void)updateFilesWithDelegate:(id<YBiCloudDelegate>)delegate __deprecated;

@end

@class YBiCloud;
/** The iCloudDelegate protocol defines the methods used to receive event notifications and allow for deeper control of the iCloud Class. */
@protocol YBiCloudDelegate <NSObject>


/** @name Optional Delegate Methods */

@optional

/** Called when the availability of iCloud changes
 
 @param cloudIsAvailable Boolean value that is YES if iCloud is available and NO if iCloud is not available 
 @param ubiquityToken An iCloud ubiquity token that represents the current iCloud identity. Can be used to determine if iCloud is available and if the iCloud account has been changed (ex. if the user logged out and then logged in with a different iCloud account). This object may be nil if iCloud is not available for any reason.
 @param ubiquityContainer The root URL path to the current application's ubiquity container. This URL may be nil until the ubiquity container is initialized. */
/**
 *  当iCloud状态改变时调用
 *
 *  @param cloudIsAvailable  iCloud开启则为YES,反之为NO
 *  @param ubiquityToken     iCloud用户
 *  @param ubiquityContainer url 跟路径
 */
- (void)iCloudAvailabilityDidChangeToState:(BOOL)cloudIsAvailable withUbiquityToken:(id)ubiquityToken withUbiquityContainer:(NSURL *)ubiquityContainer;


/** Called when the iCloud initiaization process is finished and the iCloud is available
 
 @param cloudToken An iCloud ubiquity token that represents the current iCloud identity. Can be used to determine if iCloud is available and if the iCloud account has been changed (ex. if the user logged out and then logged in with a different iCloud account). This object may be nil if iCloud is not available for any reason.
 @param ubiquityContainer The root URL path to the current application's ubiquity container. This URL may be nil until the ubiquity container is initialized. */
/**
 *  iCloud初始化完成且iCloud可用的情况下调用
 *
 *  @param cloudToken        iCloud用户
 *  @param ubiquityContainer 根URL路径
 */
- (void)iCloudDidFinishInitializingWitUbiquityToken:(id)cloudToken withUbiquityContainer:(NSURL *)ubiquityContainer;

/**
 *  指定要查询的文件类型
 *
 *  @return 返回文件类型
 */
- (NSString *)iCloudQueryLimitedToFileExtension;

/**
 *  通知代理iCloud中的文件已经被修改
 *
 *  @param files     iCloud documents文件夹中所有的文件
 *  @param fileNames 修改后的iCloud documents文件夹中所有的文件
 */
- (void)iCloudFilesDidChange:(NSMutableArray *)files withNewFileNames:(NSMutableArray *)fileNames;

/**
 *  通知代理在上传或者读取过程中本地文件和iCloud文件冲突所在的位置
 *
 *  @param cloudFile 包含iCloud文件信息的字典
 *  @param localFile 包含本地文件信息的字典
 */
- (void)iCloudFileConflictBetweenCloudFile:(NSDictionary *)cloudFile andLocalFile:(NSDictionary *)localFile;

/**
 *  通知代理在上传过程中本地文件和iCloud文件冲突所在位置，iOS 7.0之后使用，之前用iCloudFileConflictBetweenCloudFile:andLocalFile:代替
 *
 *  @param cloudFile 包含iCloud文件信息的字典
 *  @param localFile 包含本地文件信息的字典
 */
- (void)iCloudFileUploadConflictWithCloudFile:(NSDictionary *)cloudFile andLocalFile:(NSDictionary *)localFile __deprecated;
/**
 *  运行iCloud工程出错时调用
 *
 *  @param error 错误信息
 */
- (void)iCloudError:(NSError *)error __deprecated __unavailable;

/**
 *  通知代理在运行一个iCloud工程时有错误
 *
 *  @param error 错误信息
 */
- (void)cloudError:(NSError *)error __deprecated __unavailable;

/**
 *  通知代理iCloud文件已经被修改
 *
 *  @param files     修改之前iCloud document中的文件信息
 *  @param fileNames 修改后的文件信息
 */
- (void)fileListChangedWithFiles:(NSMutableArray *)files andFileNames:(NSMutableArray *)fileNames __deprecated __unavailable;

/**
 *  通知代理文件被删除
 */
- (void)documentWasDeleted __deprecated __unavailable;

/**
 *  通知代理文件已经成功保存
 */
- (void)documentWasSaved __deprecated __unavailable;

/**
 *  通知代理文件已经成功更新
 */
- (void)documentsFinishedUploading __deprecated __unavailable;

/**
 *  通知代理文件已经开始更新
 */
- (void)documentsStartedUploading __deprecated __unavailable;

/**
 *  通知代理文件已经开始下载
 */
- (void)documentsStartedDownloading __deprecated __unavailable;

/**
 *  通知代理文件下载完成
 */
- (void)documentsFinishedDownloading __deprecated __unavailable;



@end
