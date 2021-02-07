{
    "targets": [
        {
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
