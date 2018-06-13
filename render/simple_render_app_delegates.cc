//
// Created by Sunshine on 2018/5/29.
//

#include "tests/cefsimple/render/simple_render_app.h"
#include "tests/cefsimple/render/simple_render.h"

namespace simple {

void SimpleRenderApp::CreateDelegate(SimpleRenderApp::DelegateSet &delegates) {
    render::CreateDelegate(delegates);
}
}
