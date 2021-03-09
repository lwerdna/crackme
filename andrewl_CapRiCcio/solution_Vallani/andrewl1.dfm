object Form1: TForm1
  Left = 346
  Top = 253
  AlphaBlend = True
  AlphaBlendValue = 210
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'KeyGen of CapRiCcio keygenme'
  ClientHeight = 61
  ClientWidth = 383
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 289
    Height = 24
    TabOrder = 0
    Text = 'Username...'
    OnChange = Edit1Change
  end
  object Edit2: TEdit
    Left = 8
    Top = 32
    Width = 289
    Height = 24
    Color = clScrollBar
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
    Text = 'Serial...'
  end
  object BitBtn1: TBitBtn
    Left = 304
    Top = 8
    Width = 73
    Height = 48
    Caption = 'About'
    TabOrder = 2
    OnClick = BitBtn1Click
    Glyph.Data = {
      66010000424D6601000000000000760000002800000014000000140000000100
      040000000000F000000000000000000000001000000010000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
      8888888800008888888888888888888800008888888887778888888800008888
      8888600788888888000088888888E60788888888000088888888EE6888888888
      000088888888877788888888000088888888600788888888000088888888E607
      78888888000088888888E660778888880000888888888E660778888800008888
      888878E660778888000088888880778E660788880000888888660778E6078888
      0000888888E66077E608888800008888888E660066688888000088888888E666
      6E8888880000888888888EEEE888888800008888888888888888888800008888
      88888888888888880000}
  end
end
