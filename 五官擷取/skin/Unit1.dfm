object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 489
  ClientWidth = 840
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 633
    Height = 489
    Align = alLeft
    TabOrder = 0
    object StatusBar1: TStatusBar
      Left = 1
      Top = 469
      Width = 631
      Height = 19
      Panels = <
        item
          Width = 170
        end
        item
          Width = 150
        end
        item
          Width = 150
        end>
    end
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 631
      Height = 468
      ActivePage = TabSheet11
      Align = alClient
      TabOrder = 1
      object TabSheet1: TTabSheet
        Caption = #21407#22294
        object Image2: TImage
          Left = 0
          Top = 0
          Width = 201
          Height = 177
          AutoSize = True
          OnMouseMove = Image2MouseMove
        end
      end
      object TabSheet11: TTabSheet
        Caption = #25847#21462#33178#33394
        ImageIndex = 10
        ExplicitLeft = 3
        ExplicitTop = 22
        object Image16: TImage
          Left = 24
          Top = 23
          Width = 105
          Height = 105
        end
        object Image17: TImage
          Left = 255
          Top = 3
          Width = 105
          Height = 329
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 633
    Top = 0
    Width = 207
    Height = 489
    Align = alClient
    TabOrder = 1
    object Image1: TImage
      Left = 14
      Top = 303
      Width = 147
      Height = 138
      Stretch = True
      OnDblClick = Image1DblClick
    end
    object DriveComboBox1: TDriveComboBox
      Left = 5
      Top = 8
      Width = 187
      Height = 19
      DirList = DirectoryListBox1
      TabOrder = 0
    end
    object DirectoryListBox1: TDirectoryListBox
      Left = 6
      Top = 33
      Width = 187
      Height = 120
      FileList = FileListBox1
      TabOrder = 1
    end
    object FileListBox1: TFileListBox
      Left = 11
      Top = 159
      Width = 185
      Height = 138
      ItemHeight = 13
      TabOrder = 2
      OnClick = FileListBox1Click
    end
  end
  object MainMenu1: TMainMenu
    Left = 168
    Top = 416
    object File1: TMenuItem
      Caption = 'File'
    end
    object Filter1: TMenuItem
      Caption = 'Filter'
      object SKIN1: TMenuItem
        Caption = #33178#33394
        OnClick = SKIN1Click
      end
      object SKINBinary1: TMenuItem
        Caption = #33178#33394'('#20108#20540')'
        OnClick = SKINBinary1Click
      end
      object H1: TMenuItem
        Caption = #20116#23448#25847#21462
        OnClick = H1Click
      end
      object drawline1: TMenuItem
        Caption = #37002#26694
        OnClick = drawline1Click
      end
    end
  end
end
