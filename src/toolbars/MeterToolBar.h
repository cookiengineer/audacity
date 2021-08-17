/**********************************************************************

  Audacity: A Digital Audio Editor

  MeterToolbar.h

  Dominic Mazzoni
  Leland Lucius

  ToolBar to hold the VU Meter

**********************************************************************/

#ifndef __AUDACITY_METER_TOOLBAR__
#define __AUDACITY_METER_TOOLBAR__

#include "ToolBar.h"

class wxDC;
class wxGridBagSizer;
class wxSizeEvent;
class wxWindow;

class AudacityProject;
class MeterPanel;


// Constants used as bit pattern
const int kWithRecordMeter = 1;
const int kWithPlayMeter = 2;

class MeterToolBar final : public ToolBar {

 public:

   MeterToolBar(AudacityProject &project, int type);
   virtual ~MeterToolBar();
   void Create(wxWindow *parent) override;

   void Populate() override;
   void ReCreateButtons() override;
   void Repaint(wxDC * WXUNUSED(dc)) override {};
   void EnableDisableButtons() override {};
   void UpdatePrefs() override;

   void OnSize(wxSizeEvent & event);
   bool Expose(bool show) override;

   int GetInitialWidth() override {return (mWhichMeters ==
      (kWithRecordMeter + kWithPlayMeter)) ? 554 : 277;} // Separate bars used to be smaller.
   int GetMinToolbarWidth() override {return  (bHorizontal) ? 145 : toolbarSingle+11; }
   int GetMinToolbarHeight() {return  (bHorizontal) ? toolbarSingle : 145; }
   wxSize GetDockedSize() override {
      return GetSmartDockedSize();
   };
   virtual void SetDocked(ToolDock *dock, bool pushed)override;

 private:
   void RegenerateTooltips() override;

   void OnInputButton(wxCommandEvent & event);
   void OnOutputButton(wxCommandEvent & event);

   // Menu
   void ShowMenu(bool InputMenu, wxPoint pos);
   void BuildMenus(bool InputMenu);
   void ClearMenus();
   static void SetOutDevice(wxCommandEvent &);
   static void SetInDevice(wxCommandEvent &);
   static void SetChannelCount(wxCommandEvent &event);
   void OnHost(wxCommandEvent &);
   static void UpdateChannelCount();

   void OnMonitor(wxCommandEvent &);
   void OnPlayPreferences(wxCommandEvent &event);
   void OnRecPreferences(wxCommandEvent &event);


 bool bHorizontal;
   int mWhichMeters;
   wxGridBagSizer *mSizer;
   MeterPanel *mPlayMeter;
   MeterPanel *mRecordMeter;

   wxMenu *mChannelsMenu;
   wxMenu *mIOMenu;

   enum
   {
      ID_INPUT_BUTTON = 14000,
      ID_OUTPUT_BUTTON
   };

   AButton *mInButton;
   AButton *mOutButton;

 public:

   DECLARE_CLASS(MeterToolBar)
   DECLARE_EVENT_TABLE()

};

#endif

