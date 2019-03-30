#include "mailer"

public OnGameModeInit() {
    // Create the client api
    MailerRequest();

    return 1;
}

public OnPlayerCommandText(playerid, cmdtext[]) {

    if(!strcmp(cmdtext, "/sendemail", true)) {
        // Sends the email.
        SendEmail("SAMPMailer test!", "your email here", "welcome, \"Eiss\"", "This is a email test!");
        
        return 1;
    }

    return 0;
}