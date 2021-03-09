unit andrewl1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, Buttons;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit2: TEdit;
    BitBtn1: TBitBtn;
    procedure FormCreate(Sender: TObject);
    procedure Edit1Change(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  field:array[0..255] of int64;
const
s1: string='      GF(2^64)[X]/(x^64 + x^62 + x^57 + x^55 + x^54 + x^53 + x^52 + x^47 + x^46 + x^45 + x^40 + x^39 + x^38 + x^37 + x^35 + x^33 + x^32 + x^31 + x^29 + x^27 + x^24 + x^23 + x^22 + x^21 + x^19 + x^17 + x^13 + x^12 + x^10 + x^9 + x^7 + x^4 + x^1 + 1)       '+#0;

implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
var i,i2:integer;
b:boolean;
begin
for i:=0 to 255 do
begin
field[i]:=i;
for i2:=1 to 8 do
begin
b:=((field[i] mod 2)<>0);
field[i]:=field[i] shr 1;
if  b then
field[i]:=field[i] xor $C96C5795D7870F42;
end;
end;
end;

procedure TForm1.Edit1Change(Sender: TObject);
var i,i2:cardinal;
i3:int64;
s:string;
field2: array [1..8] of byte;
begin
if length(edit1.Text)<4 then edit2.Text:='Please type in at least 4 Characters...'
else if length(edit1.Text)>15 then edit2.Text:='Please type in less than 16 Characters...'
else
begin
s:=s1;
for i:=0 to (length(edit1.Text)-1) do
s[1+16*i]:=edit1.text[i+1];
i3:=$6963636972706163;
for i:=256 downto (4*length(edit1.Text)+1) do
begin
for i2:=0 to 255 do
if (field[i2] shr 56)=(i3 shr 56) then break;
i3:=i3 xor field[i2];
i3:=i3 shl 8;
if i>(4*length(edit1.Text)+8) then i3:=i3+(i2 xor ord(s[i]))
else field2[i-4*length(edit1.Text)]:=i2;
end;
i3:=0;
for i:=0 to (4*length(edit1.text)-1) do
begin
i2:=ord(s[i+1]) xor (i3 and 255);
i3:=i3 shr 8;
i3:=i3 xor field[i2];
end;
s:='';
for i:=1 to 8 do
begin
s:=inttohex((field2[i] xor (i3 and $FF)),2)+s;
i3:=i3 shr 8;
i3:=i3 xor field[field2[i]];
end;
edit2.Text:=s;
end;
end;

procedure TForm1.BitBtn1Click(Sender: TObject);
begin
MessageBox(form1.Handle,'KeyGen of CapRiCcio keygenme'#13#13'Quest Author: andrewl.us'#13#13'Solution written by Vallani'#13#13'Greetings to you fellows of crackmes.de','About...',mb_ok or mb_iconinformation); 
end;

end.
