// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_mailer
  #undef _inc_mailer
#endif
// custom include-guard to ensure we don't duplicate
#if defined _mailer_included
  #endinput
#endif
#define _mailer_included

#include <a_samp>
#include <requests>

// RequestsClient stores the client information for making requests.
static RequestsClient:client;

// MailerRequest create the requests client.
stock MailerRequest(const addr[] = "http://localhost:7788") {
    client = RequestsClient(addr);
}

// SendMail sends a POST request to our mailer API. 
stock SendEmail(name[], to[], subject[], body[]) {
    new Request:id = RequestJSON(
        client,
        "/send",
        HTTP_METHOD_POST,
        "OnPostEmailSent",
         JsonObject(
            "from",     JsonString(name),
            "to",       JsonString(to),
            "subject",  JsonString(subject),
            "body",     JsonString(body)
         )
    );

    if(!IsValidRequest(id)) {
        print("failed to send \"Mailer\" request");

        return 0;
    }

    return 1;
}

public OnRequestFailure(Request:id, errorCode, errorMessage[], len) {
    printf("Request %d failed: %d %s", _:id, errorCode, errorMessage);
}

// OnPostEmailSent is called when the request made in SendEmail has finished.
forward OnPostEmailSent(Request:id, E_HTTP_STATUS:status, Node:node);
public OnPostEmailSent(Request:id, E_HTTP_STATUS:status, Node:node) {
    if(status != HTTP_STATUS_OK) {
        printf("failed to POST email data. status=%d",
            _:status);

        return;
    }

    new
        bool: success,
        message[46];

    JsonGetBool(node, "success", success);
    JsonGetString(node, "message", message);

    if(!success) {
        printf("sent email was not sucessfull. message=\"%s\"",
            message);
        
        return;
    }

    printf("message=\"%s\"", message);
}