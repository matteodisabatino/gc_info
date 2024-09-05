{
    "targets": [
        {
            "conditions": [
                ["OS=='mac'", {
                    "xcode_settings": {
                        "MACOSX_DEPLOYMENT_TARGET": "10.9"
                    }
                }],
                ["OS=='win'", {
                    "defines": [ "NOMINMAX" ]
                }]
            ],
            "target_name": "gc_info",
            "sources": [
                "src/gc_info.cc",
                "src/event.cc",
                "src/heap_stats.cc",
                "src/gc_stats.cc"
            ],
            "include_dirs": [
                "src",
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}
