#pragma once

#include "common/Channel.hpp"
#include "common/UniqueAccess.hpp"
#include "common/UsernameSet.hpp"

namespace chatterino {

class ChannelChatters
{
public:
    ChannelChatters(Channel &channel);
    virtual ~ChannelChatters() = default;  // add vtable

    AccessGuard<const UsernameSet> accessChatters() const;

    void addRecentChatter(const QString &user);
    void addJoinedUser(const QString &user);
    void addPartedUser(const QString &user);
    void setChatters(UsernameSet &&set);
    const QColor getUserColor(const QString &user);
    void setUserColor(const QString &user, const QColor &color);
    const QString getUserPronouns(const QString &user);
    void setUserPronouns(const QString &user, const QString &pronouns);

private:
    Channel &channel_;

    // maps 2 char prefix to set of names
    UniqueAccess<UsernameSet> chatters_;
    UniqueAccess<std::map<QString, QColor>> chatterColors_;
    UniqueAccess<std::map<QString, QString>> chatterPronouns_;

    // combines multiple joins/parts into one message
    UniqueAccess<QStringList> joinedUsers_;
    bool joinedUsersMergeQueued_ = false;
    UniqueAccess<QStringList> partedUsers_;
    bool partedUsersMergeQueued_ = false;

    QObject lifetimeGuard_;
};

}  // namespace chatterino
