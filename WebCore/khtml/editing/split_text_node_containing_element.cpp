/*
 * Copyright (C) 2005 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "split_text_node_containing_element_command.h"

#include "xml/dom_textimpl.h"
#include "xml/dom_elementimpl.h"
#include "rendering/render_object.h"

#if APPLE_CHANGES
#include "KWQAssertions.h"
#else
#define ASSERT(assertion) assert(assertion)
#endif

using DOM::DocumentImpl;
using DOM::TextImpl;
using DOM::NodeImpl;
using DOM::ElementImpl;

namespace khtml {

SplitTextNodeContainingElementCommand::SplitTextNodeContainingElementCommand(DocumentImpl *document, TextImpl *text, long offset)
    : CompositeEditCommand(document), m_text(text), m_offset(offset)
{
    ASSERT(m_text);
    ASSERT(m_text->length() > 0);

    m_text->ref();
}

SplitTextNodeContainingElementCommand::~SplitTextNodeContainingElementCommand()
{
    ASSERT(m_text);
    m_text->deref();
}

void SplitTextNodeContainingElementCommand::doApply()
{
    ASSERT(m_text);
    ASSERT(m_offset > 0);

    splitTextNode(m_text, m_offset);
    
    NodeImpl *parentNode = m_text->parentNode();
    if (!parentNode->renderer() || !parentNode->renderer()->isInline()) {
        wrapContentsInDummySpan(static_cast<ElementImpl *>(parentNode));
        parentNode = parentNode->firstChild();
    }

    splitElement(static_cast<ElementImpl *>(parentNode), m_text);
}

} // namespace khtml
