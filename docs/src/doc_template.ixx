export module cmoon.docs.doc_template;

import std.core;

import cmoon.core;

namespace cmoon::docs
{
    export
    class doc_template
    {
        public:
            doc_template(std::size_t nest_level = 0)
                : nest_string{"../", nest_level} {}

            virtual ~doc_template() noexcept = default;

            friend std::ostream& operator<<(std::ostream& os, const doc_template& t)
            {
                os << cmoon::html::doctype_tag();
                os << cmoon::html::html_tag(cmoon::html::make_attributes(
                    cmoon::html::attributes::lang::constant{"en"}
                ),  cmoon::html::head_tag({},
                        cmoon::html::meta_tag(cmoon::html::make_attributes(
                            cmoon::html::attributes::charset::constant{"UTF-8"}
                        )),
                        cmoon::html::meta_tag(cmoon::html::make_attributes(
                            cmoon::html::attributes::name_{"viewport"},
                            cmoon::html::attributes::content{"width=device-width, initial-scale=1"}
                        )),
                        cmoon::html::link_tag(cmoon::html::make_attributes(
                            cmoon::html::attributes::rel::constant{"stylesheet"},
                            cmoon::html::attributes::href::constant{"css/bootstrap.min.css"}
                        )),
                        cmoon::html::link_tag(cmoon::html::make_attributes(
                            cmoon::html::attributes::rel::constant{"stylesheet"},
                            cmoon::html::attributes::href{t.nest_string + "css/main.css"}
                        )),
                        cmoon::html::link_tag(cmoon::html::make_attributes(
                            cmoon::html::attributes::rel::constant{"stylesheet"},
                            cmoon::html::attributes::href{t.nest_string + "css/default.min.css"}
                        ))
                    ),
                    cmoon::html::body_tag(cmoon::html::make_attributes(
                        cmoon::html::attributes::class_::constant{"lh-sm"}
                    ),  cmoon::html::div_tag(cmoon::html::make_attributes(
                            cmoon::html::attributes::id::constant{"header"}
                        ),  cmoon::html::nav_tag(cmoon::html::make_attributes(
                                cmoon::html::attributes::class_::constant{"navbar navbar-expand-lg navbar-light bg-light"}
                            ),  cmoon::html::div_tag(cmoon::html::make_attributes(
                                    cmoon::html::attributes::class_::constant{"container-fluid"}
                                ),  cmoon::html::a_tag(cmoon::html::make_attributes(
                                        cmoon::html::attributes::class_::constant{"navbar-brand"},
                                        cmoon::html::attributes::href{t.nest_string + "index.html"}
                                    ),  "C++ Docs"
                                    ),
                                    cmoon::html::button_tag(cmoon::html::make_attributes(
                                        cmoon::html::attributes::class_::constant{"navbar-toggler"},
                                        cmoon::html::attributes::type::constant{"button"},
                                        cmoon::html::attributes::data_bs_toggle::constant{"collapse"},
                                        cmoon::html::attributes::data_bs_target::constant{"#navbarSupportedContent"},
                                        cmoon::html::attributes::aria_controls::constant{"navbarSupportedContent"},
                                        cmoon::html::attributes::aria_expanded::constant{"false"},
                                        cmoon::html::attributes::aria_label::constant{"Toggle navigation"}
                                    ),  cmoon::html::span_tag(cmoon::html::make_attributes(
                                            cmoon::html::attributes::class_::constant{"navbar-toggler-icon"}
                                        ))
                                    ),
                                    cmoon::html::div_tag(cmoon::html::make_attributes(
                                        cmoon::html::attributes::class_::constant{"collapse navbar-collapse"},
                                        cmoon::html::attributes::id::constant{"navbarSupportedContent"}
                                    ),  cmoon::html::ul_tag(cmoon::html::make_attributes(
                                            cmoon::html::attributes::class_::constant{"navbar-nav me-auto mb-2 mb-lg-0"}
                                        ),  cmoon::html::a_tag(cmoon::html::make_attributes(
                                                cmoon::html::attributes::class_::constant{"link-dark"},
                                                cmoon::html::attributes::href::constant{github_url}
                                            ), github_logo
                                            )
                                        ),
                                        cmoon::html::form_tag(cmoon::html::make_attributes(
                                            cmoon::html::attributes::class_::constant{"d-flex"},
                                            cmoon::html::attributes::method::constant{"get"},
                                            cmoon::html::attributes::action::constant{"https://duckduckgo.com/"}
                                        ),  cmoon::html::input_tag(cmoon::html::make_attributes(
                                                cmoon::html::attributes::class_::constant{"form-control me-2"},
                                                cmoon::html::attributes::name_::constant{"q"},
                                                cmoon::html::attributes::type::constant{"text"},
                                                cmoon::html::attributes::placeholder::constant{"Search"},
                                                cmoon::html::attributes::aria_label::constant{"Search"},
                                                cmoon::html::attributes::required{}
                                            )),
                                            cmoon::html::input_tag(cmoon::html::make_attributes(
                                                cmoon::html::attributes::class_::constant{"visually-hidden"},
                                                cmoon::html::attributes::name_::constant{"sites"},
                                                cmoon::html::attributes::id::constant{"search_sites"}
                                            )),
                                            cmoon::html::input_tag(cmoon::html::make_attributes(
                                                cmoon::html::attributes::class_::constant{"btn btn-outline-success"},
                                                cmoon::html::attributes::type::constant{"submit"},
                                                cmoon::html::attributes::value::constant{"Submit"}
                                            ))
                                        )
                                    )
                                )
                            )
                        ),
                        cmoon::html::div_tag(cmoon::html::make_attributes(
                            cmoon::html::attributes::id::constant{"content"},
                            cmoon::html::attributes::class_::constant{"container"}
                        ),  cmoon::html::nav_tag(cmoon::html::make_attributes(
                                cmoon::html::attributes::class_::constant{"my-3 pe-2 ps-2 bg-light border rounded d-inline-flex"},
                                cmoon::html::attributes::style::constant{"--bs-breadcrumb-divider: url(&#34;data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='8' height='8'%3E%3Cpath d='M2.5 0L1 1.5 3.5 4 1 6.5 2.5 8l4-4-4-4z' fill='currentColor'/%3E%3C/svg%3E&#34;);"},
                                cmoon::html::attributes::aria_label::constant{"breadcrumb"}
                            ),  cmoon::html::ol_tag(cmoon::html::make_attributes(
                                    cmoon::html::attributes::class_::constant{"breadcrumb mb-1"}
                                ))
                            ),
                            t.content()
                        )
                    )
                );

                return os;
            }

        protected:
            static constexpr std::string_view github_url {"https://github.com/mooncollin/CPPAdditions"};
            static constexpr auto github_logo {cmoon::html::svg_tag(cmoon::html::make_attributes(
                cmoon::html::attributes::xmlns::constant{"http://www.w3.org/2000/svg"},
                cmoon::html::attributes::width::constant<24>{},
                cmoon::html::attributes::height::constant<24>{},
                cmoon::html::attributes::viewbox::constant{"0 0 24 24"}
            ),  cmoon::html::path_tag(cmoon::html::make_attributes(
                    cmoon::html::attributes::d::constant{"M12 0c-6.626 0-12 5.373-12 12 0 5.302 3.438 9.8 8.207 11.387.599.111.793-.261.793-.577v-2.234c-3.338.726-4.033-1.416-4.033-1.416-.546-1.387-1.333-1.756-1.333-1.756-1.089-.745.083-.729.083-.729 1.205.084 1.839 1.237 1.839 1.237 1.07 1.834 2.807 1.304 3.492.997.107-.775.418-1.305.762-1.604-2.665-.305-5.467-1.334-5.467-5.931 0-1.311.469-2.381 1.236-3.221-.124-.303-.535-1.524.117-3.176 0 0 1.008-.322 3.301 1.23.957-.266 1.983-.399 3.003-.404 1.02.005 2.047.138 3.006.404 2.291-1.552 3.297-1.23 3.297-1.23.653 1.653.242 2.874.118 3.176.77.84 1.235 1.911 1.235 3.221 0 4.609-2.807 5.624-5.479 5.921.43.372.823 1.102.823 2.222v3.293c0 .319.192.694.801.576 4.765-1.589 8.199-6.086 8.199-11.386 0-6.627-5.373-12-12-12z"}
                ))
            )};

            virtual cmoon::html::dynamic_element<> content() const
            {
                return cmoon::html::dynamic_element<>{"div", cmoon::html::no_attributes, "This is the content!"};
            }

            virtual const std::vector<std::pair<std::string, std::string>>& breadcrumbs_data() const
            {
                static std::vector<std::pair<std::string, std::string>> v;
                return v;
            }

            auto breadcrumbs() const
            {
                cmoon::html::dynamic_elements crumbs;

                const auto& data {breadcrumbs_data()};

                for (auto it {data.begin()}; it != data.end(); ++it)
                {
                    const auto& [name, url] = *it;

                    if (it != (data.end() - 1))
                    {
                        crumbs.push_back(
                            cmoon::html::li_tag(cmoon::html::make_attributes(
                                cmoon::html::attributes::class_::constant{"breadcrumb-item action"}
                            ),  cmoon::html::a_tag(cmoon::html::make_attributes(
                                    cmoon::html::attributes::href{url}
                                ),  name
                                )
                            )
                        );
                    }
                    else
                    {
                        crumbs.push_back(
                            cmoon::html::li_tag(cmoon::html::make_attributes(
                                cmoon::html::attributes::class_::constant{"breadcrumb-item active"},
                                cmoon::html::attributes::aria_current::constant{"page"}
                            ),  name
                            )
                        );
                    }
                }

                return cmoon::html::ol_tag(cmoon::html::make_attributes(
                    cmoon::html::attributes::class_::constant{"breadcrumb mb-1"}
                ),  crumbs
                );
            }
        private:
            std::string nest_string;
    };
}