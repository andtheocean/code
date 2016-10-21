# -*- coding: utf-8 -*-
# @Author: copbint
# @Date:   2016-03-13 12:48:57
# @Last Modified by:   copbint
# @Last Modified time: 2016-03-13 15:01:46

import scrapy
from weather.items import WeatherItem

class weatherSpider(scrapy.Spider):
    name = "myweather"
    allowed_domains = ["sina.come.cn"]
    start_urls = ['http://weather.sina.com.cn']

    def parse(self,response):
        item = WeatherItem()
        item['city'] = response.xpath('//*[@id="slider_ct_name"]/text()').extract()
        tenDay = response.xpath('//*[@id="blk_fc_c0_scroll"]');
        item['date'] = tenDay.css('p.wt_fc_c0_i_date::text').extract()
        item['date_weather'] = tenDay.css('img.icons0_wt::attr(title)').extract()
        item['date_temperature'] = tenDay.css('p.wt_fc_c0_i_temp::text').extract()
        return item



