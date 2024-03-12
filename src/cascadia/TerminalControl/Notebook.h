// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include "Notebook.g.h"
#include "EventArgs.h"
#include "../../renderer/base/Renderer.hpp"
#include "../../renderer/uia/UiaRenderer.hpp"
#include "../../cascadia/TerminalCore/Terminal.hpp"
#include "../../cascadia/TerminalCore/BlockRenderData.hpp"
#include "../buffer/out/search.h"

#include "ControlInteractivity.h"
#include "ControlSettings.h"

namespace winrt::Microsoft::Terminal::Control::implementation
{
    struct NotebookBlock
    {
        std::unique_ptr<::Microsoft::Terminal::Core::BlockRenderData> renderData{ nullptr };
        winrt::com_ptr<Microsoft::Terminal::Control::implementation::ControlCore> core{ nullptr };
        Microsoft::Terminal::Control::TermControl control{ nullptr };
    };

    struct Notebook : NotebookT<Notebook>
    {
    public:
        Notebook(Control::IControlSettings settings, Control::IControlAppearance unfocusedAppearance, TerminalConnection::ITerminalConnection connection);
        Windows::Foundation::Collections::IVector<Microsoft::Terminal::Control::TermControl> Controls() const;
        Microsoft::Terminal::Control::TermControl ActiveControl() const;

        til::typed_event<Control::Notebook, Control::TermControl> NewBlock;

    private:
        std::shared_ptr<::Microsoft::Terminal::Core::Terminal> _terminal{ nullptr };
        TerminalConnection::ITerminalConnection _connection{ nullptr };
        Control::IControlSettings _settings{ nullptr };
        Control::IControlAppearance _unfocusedAppearance{ nullptr };
        bool _gotFirstMark{ false };
        std::vector<NotebookBlock> _blocks{};

        winrt::fire_and_forget _fork(const til::CoordType start);
    };
}

namespace winrt::Microsoft::Terminal::Control::factory_implementation
{
    BASIC_FACTORY(Notebook);
}