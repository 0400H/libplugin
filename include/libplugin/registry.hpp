namespace libplugin {

class registry {
public:
    std::shared_ptr<libplugin::container> get_container();
};

}