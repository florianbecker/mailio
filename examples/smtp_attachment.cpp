/*

smtps_attachment.cpp
--------------------
 
Connects to an SMTP server via SSL and sends a message with attached files.

 
Copyright (C) 2016, Tomislav Karastojkovic (http://www.alepho.com).

Distributed under the FreeBSD license, see the accompanying file LICENSE or
copy at http://www.freebsd.org/copyright/freebsd-license.html.

*/


#include <iostream>
#include <fstream>
#include <list>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>


using mailio::message;
using mailio::string_t;
using mailio::mail_address;
using mailio::smtp;
using mailio::smtp_error;
using mailio::dialog_error;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::tuple;
using std::make_tuple;
using std::list;


int main()
{
    try
    {
        // create mail message
        message msg;
        msg.from(mail_address("mailio library", "mailio@gmail.com"));// set the correct sender name and address
        msg.add_recipient(mail_address("mailio library", "mailio@gmail.com"));// set the correct recipent name and address
        msg.subject("smtps message with attachment");
        msg.content("Here are Aleph0 and Infinity pictures.");

        ifstream ifs1("aleph0.png", std::ios::binary);
        ifstream ifs2("infinity.png", std::ios::binary);
        list<tuple<std::istream&, string_t, message::content_type_t>> atts;
        atts.push_back(make_tuple(std::ref(ifs1), "aleph0.png", message::content_type_t(message::media_type_t::IMAGE, "png")));
        atts.push_back(make_tuple(std::ref(ifs2), "infinity.png", message::content_type_t(message::media_type_t::IMAGE, "png")));
        msg.attach(atts);

        // use a server to login over tls connectivity
        smtp conn("smtp.mailserver.com", 465);
        conn.start_tls(false);
        // modify username/password to use real credentials
        conn.authenticate("mailio@mailserver.com", "mailiopass", smtp::auth_method_t::LOGIN);
        conn.submit(msg);
    }
    catch (smtp_error& exc)
    {
        cout << exc.what() << endl;
    }
    catch (dialog_error& exc)
    {
        cout << exc.what() << endl;
    }

    return EXIT_SUCCESS;
}
