#pragma once


#define SET_MESSAGE_RESPONSE(VAR, RESPONSE, MESSAGE_NAME) \
    if (RESPONSE.get() && RESPONSE->has_## MESSAGE_NAME()) \
        VAR.Set(RESPONSE, &RESPONSE->MESSAGE_NAME());     \
    else                                                  \
        VAR.Set(RESPONSE, nullptr);

#define SET_SUBMESSAGE_RESPONSE(VAR, MESSAGE, SUBMESSAGE_NAME)       \
    if (!MESSAGE.HasErrors() && MESSAGE->has_## SUBMESSAGE_NAME())    \
        VAR.Set(MESSAGE.GetResponse(), &MESSAGE->SUBMESSAGE_NAME()); \
    else                                                             \
        VAR.Set(MESSAGE.GetResponse(), nullptr);
