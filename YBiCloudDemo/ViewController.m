//
//  ViewController.m
//  YBiCloudDemo
//
//  Created by 曹燕兵 on 16/3/2.
//  Copyright © 2016年 曹燕兵. All rights reserved.
//

#import "ViewController.h"
#import "YBiCloud.h"
@interface ViewController ()
@end

@implementation ViewController
{
    NSMutableArray *fileNameList;
    NSMutableArray *fileObjectList;
    UIRefreshControl *refreshControl;
    
}
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    YBiCloud *cloud = [YBiCloud sharedCloud];
    cloud.delegate = self;
    cloud.verboseLogging = YES;
    if (fileNameList == nil) fileNameList = [NSMutableArray array];
    if (fileObjectList == nil) fileObjectList = [NSMutableArray array];
    //    NSDictionary * dict = @{@"aa":@"11"};
    //    [cloud saveAndCloseDocumentWithName:@"11.text" withContent:(NSData*)dict completion:^(UIDocument *cloudDocument, NSData *documentData, NSError *error) {
    //    }];
    // Display an Edit button in the navigation bar for this view controller.
    //    self.navigationItem.rightBarButtonItem = self.editButtonItem;
    
    // Create refresh control
    //    if (refreshControl == nil) refreshControl = [[UIRefreshControl alloc] init];
    //    [refreshControl addTarget:self action:@selector(refreshCloudList) forControlEvents:UIControlEventValueChanged];
    //    [self.view addSubview:refreshControl];
    NSString *str = @"11111111111";
    NSData *data = [str dataUsingEncoding:NSUTF8StringEncoding];
    //在iCloud创建文件
    //    [cloud saveAndCloseDocumentWithName:@"mytest.text" withContent:data completion:^(UIDocument *cloudDocument, NSData *documentData, NSError *error) {
    //        if (error ==nil) {
    //            NSLog(@"%@",cloudDocument);
    //            NSLog(@"%@",documentData);
    //        }
    //    }];
    YBiCloudDocument *cloudDocument = [cloud retrieveCloudDocumentObjectWithName:@"mytest.text"];
    [cloud retrieveCloudDocumentWithName:@"mytest.text" completion:^(UIDocument *cloudDocument, NSData *documentData, NSError *error) {
        NSLog(@"%@*****",documentData);
        NSString *string = [[NSString alloc]initWithData:documentData encoding:NSUTF8StringEncoding];
        NSLog(@"%@",string);
        
    }];
    //    [cloud renameOriginalDocument:@"mytest.text" withNewName:@"second.text" completion:^(NSError *error) {
    //        NSLog(@"修改成功！");
    //    }];
    //    [cloud doesFileExistInCloud:@"mytest.text"];
    //    [cloud doesFileExistInCloud:@"second.text"];
    //    [cloud getListOfCloudFiles];
    //    [cloud deleteDocumentWithName:@"mytest.text" completion:^(NSError *error) {
    //        NSLog(@"删除成功");
    //    }];
    //    NSLog(@"%@",[cloud getListOfCloudFiles]);
    //分享
    //   NSURL *url = [cloud shareDocumentWithName:@"mytest.text" completion:^(NSURL *sharedURL, NSDate *expirationDate, NSError *error) {
    //
    //   }];
    //    NSLog(@"%@",url);
    // Subscribe to iCloud Ready Notifications
}
- (void)refreshCloudList {
    [[YBiCloud sharedCloud] updateFiles];
}

@end
