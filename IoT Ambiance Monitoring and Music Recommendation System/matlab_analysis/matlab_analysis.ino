readAPIKey = 'WU6ABUMH50QRC20V'; % Replace with your ThingSpeak Read API
Key
channelID = 2762875; % Replace with your ThingSpeak Channel ID
threshold1 = 20; % Humidity Threshold value and
threshold2 = 20; % Temperature Threshold value to trigger Spotify
playlisy follow
% IFTTT Webhook URL
iftttWebhookURL =
'https://maker.ifttt.com/trigger/Mood_Change/with/key/cvRPM4rxwvQmnVOQlZ
smSVweF0uS32lldGbjvuo3xZ4';
% Read data from both fields
field1 = thingSpeakRead(channelID, 'Fields', 1, 'ReadKey', readAPIKey);
field2 = thingSpeakRead(channelID, 'Fields', 2, 'ReadKey', readAPIKey);
% Check if both thresholds are met
if isscalar(field1) && isscalar(field2) && field1 > threshold1 && field2
> threshold2
 webwrite(iftttWebhookURL, 'value1', field1, 'value2', field2); %
trigger the webhook
 disp('Webhook triggered.');
else
 disp('Thresholds not met.');
end