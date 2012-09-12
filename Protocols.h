/*
 *  Protocols.h
 *  Navigation Bar
 *
 *  Created by Victor Borshak on 21.04.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

/*
 *  Protocols.h
 *
 *  Created by Victor Borshak.
 *  Copyright 2007 LikeMac Group. All rights reserved.
 *
 */


typedef enum _DiskOrderPluginsType {
	GENERAL_PLUGIN_TYPE = 1,
	ARCHIVE_PLUGIN_TYPE = 2,
	VIEWER_PLUGIN_TYPE = 3,
	LAUNCH_PLUGIN_TYPE = 4
} DiskOrderPluginsType;


@protocol DiskOrderProtocol

- (NSWindow *) mainWindow;
- (NSString *) sourcePath;
- (NSString *) targetPath;
- (void) switchDiskOrderToPath:(NSString *)path;

- (void) subscribeTargetToSelectionChange:(id)target selector:(SEL)selector;
- (void) subscribeTargetToLocationChange:(id)target selector:(SEL)selector;

- (void) unsubscribeTargetFromSelectionChange:(id)target;
- (void) unsubscribeTargetFromLocationChange:(id)target;

- (NSArray *) mountedFileSystems;
- (id) activeFileSystem;
- (void) activateFileSystem:(id) fileSystem;

// AVAILABE_IN_DISKORDER_2_5_2_AND_HIGHER
- (void) mountFileSystem:(id) fileSystem;
// END_OF_AVAILABE_IN_DISKORDER_2_5_2_AND_HIGHER

- (BOOL) unmountFileSystem:(id) fileSystem;


- (void) updateDirectoryAtPath:(NSString *)path;
- (void) copyPaths:(NSArray *)paths toDestination:(NSString*)dest askOk:(BOOL)ask;
- (void) movePaths:(NSArray *)paths toDestination:(NSString*)dest askOk:(BOOL)ask;
- (void) moveToTrashFileAtPath:(NSArray *)paths askOk:(BOOL)ask;

- (void) viewFileAtPath:(NSString *)path;
- (void) editFileAtPath:(NSString *)path;
- (void) getInfoForFileAtPath:(NSString *)path;

- (void) notifyDiskOrderOnPluginUnload:(NSString *)identifier;

@end

@protocol LMFileSystemProtocol

- (NSString *) identifier;               // Any identifier. Used as a mount point name for your file system
- (void) setIdentifier:(NSString *) identifier;

- (NSString *) description;              // Return something like "MyCustom file system"
- (NSString *) realPathToFileSystem;

- (NSImage *) fileSystemIcon;            // Icon to be displayed along with your file system

- (BOOL) allowsSharedAccess;
- (BOOL) shouldHaveMountpoint;           // Should your file system be mounted in Disk Order & displayed in drives pane????

- (void) setCurrentDirectory:(NSString *)thePath;
- (NSString *)currentDirectory;

- (NSArray *)directoryContentsAtPath:(NSString*) path;
- (NSDictionary*) getAttributesForItemAtPath:(NSString*)path;

- (BOOL) isReadablePath:(NSString*)path;
- (BOOL) isWritablePath:(NSString*)path;

- (BOOL) renamePath:(NSString*)sourcePath toPath:(NSString*)targetPath;
- (BOOL) deletePath:(NSString*) path;
- (BOOL) createDirectory:(NSString*) path;

- (int) downloadFileFrom:(NSString *)sourcePath local:(NSString *)targetPath callBack:(unsigned long long *) var;
- (int) uploadFileTo:(NSString *)targetPath local:(NSString *)sourcePath callBack:(unsigned long long *) var;
- (void) displayInfoWindowForPath:(NSString*)path;
- (BOOL) activateItemAtPath:(NSString*)path;

- (void) resetAbortFlag;
- (void) abortAction;                      // Called when user aborts the current action. Downloading or uploading files, for example
- (BOOL) isAborted;

- (NSString *)lastError;                   // Returns the last error that occured in your file system

- (BOOL) isBusy;                           // Is the file system busy right now. Disk Order won't allow to unmount it if so...
- (void) closeFileSystem;                  // just do anything here when Disk Order unmounts the file system

@end


// The main (root) protocol of Disk Order plugin
@protocol LMDiskOrderPlugin

- (NSString *) plugInName;              // Name of Plugin
- (unsigned) interfaceVersion;          // Version protocol
- (NSString *) authorName;              // author's name
- (NSString *) pluginDescription;       // desription of plugin
- (NSString *) menuItemString;          // menu string
- (DiskOrderPluginsType) pluginType;    // type of plugin
- (Class) pluginClass;

@end

// Not yet complete. Don't use it
@protocol LMArchiveDiskOrderPlugin <LMFileSystemProtocol>

+ (NSArray*) formats;
+ (NSString*) defaultExtension;
+ (BOOL) supportsFileSystemProtocol;

- (id) initWithArchiveAtPath:(NSString *) pathToArchive;

- (void) addFiles:(NSArray*) paths toArchivedPath:(NSString*) pathInArchive;
- (void) getFiles:(NSArray*) archivedPaths toLocation:(NSString*) localPath;

+ (void) createArchiveWith:(NSArray *) paths at:(NSString*) localPath;
+ (void) unpackArchive:(NSString*) pathToArchive to:(NSString*) localPath;
@end

@protocol LMGeneralDiskOrderPlugin
- (BOOL) shouldAppeaarInToolbar;
- (NSString *) toolBarIconName;
- (NSString *) uniqueIdentifier;
- (int) startOperationWithPaths:(NSArray *)paths diskOrder:(id)diskOrder;
- (BOOL) shouldAutostart;
- (BOOL) shouldAppearInExtrasMenu;
- (BOOL) allowsManyInstances;
- (void) unload;
@end

@protocol LMSendToDiskOrderPlugin <LMGeneralDiskOrderPlugin>
- (NSString *)itemTitle;
- (int) startOperationWithPaths:(NSArray *)paths diskOrder:(id)diskOrder withObject:(id)paramObj;
- (NSDictionary *) getNewItemAttributes:(NSWindow *)parentWindow;
- (NSDictionary *) changeAttributesForItemWithTitle:(NSString *)title paramString:(NSString*) paramString paramObj:(id)paramObj parentWindow:(NSWindow*)parentWindow;
@end

