
static int test_probe (struct platform_device *pdev) {
    return 0;
}

static int test_remove (struct platform_device *pdev) {
    return 0;
}

const struct of_device_id of_mtk_match[] = {
    {.compatible = "test, platform-v1" },
    {.compatible = "test, platform-v2" },
    {.compatible = "test, platform-v3" },
};
MODULE_DEVICE_TABLE(of, of_mtk_match);

static struct platform_driver test_driver = {
	.probe = test_probe,
	.remove = test_remove,
	.driver = {
		.name = "test, platform",
		.of_match_table = of_mtk_match,
	},
};

// platform_driver_register(&test_driver);
// platform_driver_unregister(&test_driver);