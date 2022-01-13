#ifndef SVCommonPluginInterfaceH
#define SVCommonPluginInterfaceH

#include <QtPlugin>
class QWidget;

/*! This class declares common plugin interface functions.
	This header should be included by all plugin interface classes.
*/
class SVCommonPluginInterface {
public:
	/*! Return values for the showSettingsDialog() function. */
	enum SettingsDialogUpdateNeeds {
		/*! No update needed. */
		NoUpdate,
		/*! Something has changed that affects the display in the scene,
			for example colors (maybe component colors).
		*/
		SceneUpdate = 0x01,
		/*! Something has changed related to databases and all widgets
			showing database content (colors, names, labels) shall be updated.
		*/
		DatabaseUpdate = 0x02
	};

	/*! Virtual D'tor. */
	virtual ~SVCommonPluginInterface() = default;

	/*! Returns a title text for the plugin, used in the main menu for settings and
		for info/error messages. Used like "Configure xxxx..." and "About xxxx...".
	*/
	virtual QString title() const = 0;

	/*! If this function returns true, the plugin provides a
		settings/configuration page.
	*/
	virtual bool hasSettingsDialog() const { return false; }

	/*! If a settings dialog page is provided, this function is called when
		the user clicks on the respective settings dialog menu entry.
		\param parent Parent class pointer, to be used as parent for modal dialogs.
		\return Returns a bitmask that signals what kind of update is needed
			in the user-interface as consequence of the settings dialogs
			changes (see SettingsDialogUpdateNeeds).
	*/
	virtual int showSettingsDialog(QWidget * parent) { (void)parent; return NoUpdate; }
};


Q_DECLARE_METATYPE(SVCommonPluginInterface*)

#endif // SVCommonPluginInterfaceH
