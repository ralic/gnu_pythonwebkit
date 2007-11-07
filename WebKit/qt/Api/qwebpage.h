/*
    Copyright (C) 2007 Trolltech ASA
    Copyright (C) 2007 Staikos Computing Services Inc.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

    This class provides all functionality needed for loading images, style sheets and html
    pages from the web. It has a memory cache for these objects.
*/

#ifndef QWEBPAGE_H
#define QWEBPAGE_H

#include "qwebpagehistory.h"
#include "qwebsettings.h"
#include <qwebkitglobal.h>

#include <qwidget.h>
class QNetworkProxy;
class QUndoStack;
class QUrl;
class QWebFrame;
class QWebNetworkRequest;

class QWebPagePrivate;
class QWebFrameData;
class QWebNetworkInterface;

namespace WebCore {
    class ChromeClientQt;
    class FrameLoaderClientQt;
    class FrameLoadRequest;
    class EditorClientQt;
    class ResourceHandle;
}

class QWEBKIT_EXPORT QWebPage : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool modified READ isModified)
public:
    enum NavigationRequestResponse {
        AcceptNavigationRequest,
        IgnoreNavigationRequest
    };

    enum NavigationType {
        NavigationTypeLinkClicked,
        NavigationTypeFormSubmitted,
        NavigationTypeBackForward,
        NavigationTypeReload,
        NavigationTypeFormResubmitted,
        NavigationTypeOther
    };

    enum WebAction {
        NoWebAction = - 1,

        OpenLinkInNewWindow,
        OpenFrameInNewWindow,

        DownloadLinkToDisk,
        CopyLinkToClipboard,

        OpenImageInNewWindow,
        DownloadImageToDisk,
        CopyImageToClipboard,

        GoBack,
        GoForward,
        Stop,
        Reload,

        Cut,
        Copy,
        Paste,

        Undo,
        Redo,
        MoveToNextChar,
        MoveToPreviousChar,
        MoveToNextWord,
        MoveToPreviousWord,
        MoveToNextLine,
        MoveToPreviousLine,
        MoveToStartOfLine,
        MoveToEndOfLine,
        MoveToStartOfBlock,
        MoveToEndOfBlock,
        MoveToStartOfDocument,
        MoveToEndOfDocument,
        SelectNextChar,
        SelectPreviousChar,
        SelectNextWord,
        SelectPreviousWord,
        SelectNextLine,
        SelectPreviousLine,
        SelectStartOfLine,
        SelectEndOfLine,
        SelectStartOfBlock,
        SelectEndOfBlock,
        SelectStartOfDocument,
        SelectEndOfDocument,
        DeleteStartOfWord,
        DeleteEndOfWord,

        NumWebActions = DeleteEndOfWord
    };


    QWebPage(QWidget *parent);
    ~QWebPage();

    void open(const QUrl &url);
    void open(const QWebNetworkRequest &request);

    QWebFrame *mainFrame() const;

    QWebPageHistory *history() const;

    // ### owned by webpage, returns a pointer, no setter!
    void setSettings(const QWebSettings &settings);
    QWebSettings settings() const;

    QSize sizeHint() const;

    // ### should be windowTitle
    QString title() const;
    QUrl url() const;
    // ### should be QWidget::icon
    QPixmap icon() const;

    bool isModified() const;
    QUndoStack *undoStack();
    
    void setNetworkInterface(QWebNetworkInterface *interface);
    QWebNetworkInterface *networkInterface() const;

#ifndef QT_NO_NETWORKPROXY
    void setNetworkProxy(const QNetworkProxy& proxy);
    QNetworkProxy networkProxy() const;
#endif

    // #### remove after adding editor actions
    bool canCut() const;
    bool canCopy() const;
    bool canPaste() const;

    quint64 totalBytes() const;
    quint64 bytesReceived() const;

public slots:
    /**
     * Stops loading of the page, if loading.
     */
    void stop();

    // #### should these be actions?
    void goBack();
    void goForward();
    void goToHistoryItem(const QWebHistoryItem &item);

    // ### should be a signal: void geometryChangeRequest(const QRect &geom);
    virtual void setWindowGeometry(const QRect& geom);

    void cut();
    void copy();
    void paste();
    // ### should we have execCommand() or something similar?

signals:
    /**
     * Signal is emitted when load is started on one of the child
     * frames of the page. The frame on which the load started
     * is passed.
     */
    void loadStarted(QWebFrame *frame);
    /**
     * Signal is emitted when the global progress status changes.
     * It accumulates changes from all the child frames.
     */
    void loadProgressChanged(int progress);
    /**
     * Signal is emitted when load has been finished on one of
     * the child frames of the page. The frame on which the
     * load finished is passed as an argument.
     */
    void loadFinished(QWebFrame *frame);
    /**
     * Signal is emitted when the title of this page has changed.
     * Applies only to the main frame.  Sub-frame titles do not trigger this.
     */
    void titleChanged(const QString& title);
    /**
     * Signal is emitted when the mouse is hovering over a link.
     * The first parameter is the link url, the second is the link title
     * if any. Method is emitter with both empty parameters when the mouse
     * isn't hovering over any link element.
     */
    void hoveringOverLink(const QString &link, const QString &title);
    /**
     * Signal is emitted when the statusbar text is changed by the page.
     */
    void statusBarTextChanged(const QString& text);
    /**
     * Signal is emitted when an icon ("favicon") is loaded from the site.
     */
    void iconLoaded();

    // #### doesn't give you anything without a way to actually get the selection
    void selectionChanged();

    /**
      * Signal is emitted when the mainframe()'s initial layout is completed.
     */
    void initialLayoutComplete();

    void addToHistory(const QUrl&);

    void frameCreated(QWebFrame *frame);

protected:
    virtual QWebPage *createWindow();
    virtual QWebPage *createModalDialog();
    virtual QObject *createPlugin(const QString &classid, const QUrl &url, const QStringList &paramNames, const QStringList &paramValues);

    virtual void webActionTriggered(WebAction action, bool checked = false);

    virtual NavigationRequestResponse navigationRequested(QWebFrame *frame, const QWebNetworkRequest &request, NavigationType type);
    // ### what does this do?
    virtual QString chooseFile(QWebFrame *frame, const QString& oldFile);
    // ### can we unify the next 3 methods? 
    virtual void javaScriptAlert(QWebFrame *frame, const QString& msg);
    virtual bool javaScriptConfirm(QWebFrame *frame, const QString& msg);
    virtual bool javaScriptPrompt(QWebFrame *frame, const QString& msg, const QString& defaultValue, QString* result);
    virtual void javaScriptConsoleMessage(const QString& message, unsigned int lineNumber, const QString& sourceID);

    // ### should the be here?
    virtual QString userAgentStringForUrl(const QUrl& forUrl) const;

    virtual void resizeEvent(QResizeEvent*);
    virtual void paintEvent(QPaintEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseDoubleClickEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void contextMenuEvent(QContextMenuEvent*);
    virtual void wheelEvent(QWheelEvent*);
    virtual void keyPressEvent(QKeyEvent*);
    virtual void keyReleaseEvent(QKeyEvent*);
    virtual void focusInEvent(QFocusEvent*);
    virtual void focusOutEvent(QFocusEvent*);
    virtual bool focusNextPrevChild(bool next);

    virtual void dragEnterEvent(QDragEnterEvent *);
    virtual void dragLeaveEvent(QDragLeaveEvent *);
    virtual void dragMoveEvent(QDragMoveEvent *);
    virtual void dropEvent(QDropEvent *);

private:
    Q_PRIVATE_SLOT(d, void _q_onLoadProgressChanged(int))
    friend class QWebFrame;
    friend class QWebPagePrivate;
    friend class WebCore::ChromeClientQt;
    friend class WebCore::EditorClientQt;
    friend class WebCore::FrameLoaderClientQt;
    friend class WebCore::ResourceHandle;
    QWebPagePrivate *d;
};



#endif
