// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026  Vladimir Osipov
#include "backend_factory.h"

#include "backend/backend.h"
#include "backend/imap/imap_auth.h"
#include "backend/imap/imap_backend.h"
#include "backend/slack/public_backend.h"
#include "backend/slack/slack_auth.h"
#include "backend/teams/teams_auth.h"
#include "backend/teams/teams_backend.h"
#if defined(MSGA_DEMO)
#include "backend/demo/demo_backend.h"
#include "backend/demo/demo_fixture.h"
#include <QDebug>
#endif

std::unique_ptr<Backend> makeBackend(const TokenStore::WorkspaceRecord &rec) {
    switch (rec.key.service) {
    case Service::Slack:
        // The only place Slack credential types appear above the adapter: the
        // switch case that builds the Slack backend. slack::PublicBackend reads
        // its own app-config + acquires the refcounted shared Socket Mode socket.
        return std::make_unique<slack::PublicBackend>(slack::fromRecord(rec));
    case Service::Teams:
        // Microsoft Teams over Graph (delegated). teams::Backend reads its own
        // compiled-in app-config and decodes the per-service auth blob.
        return std::make_unique<teams::Backend>(teams::fromRecord(rec));
    case Service::Imap:
        // Email over IMAP/SMTP (imap-backend-plan §1). imap::Backend decodes its
        // own credentials blob and connects on construction.
        return std::make_unique<imap::Backend>(imap::fromRecord(rec));
#if defined(MSGA_DEMO)
    case Service::Demo: {
        // The auth blob is the fixture directory (demo::seedWorkspace wrote it).
        QString error;
        auto    fx = demo::loadFixture(QString::fromUtf8(rec.auth), &error);
        if (!fx) {
            qWarning() << "demo fixture:" << error;
            return nullptr;
        }
        return std::make_unique<demo::DemoBackend>(std::move(*fx));
    }
#endif
    }
    return nullptr;
}
